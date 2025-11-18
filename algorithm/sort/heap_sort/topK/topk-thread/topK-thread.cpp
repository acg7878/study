#include <algorithm>
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

// --- 最小堆核心函数 ---

// 将子树堆化（最小堆）
void heapify(std::vector<long long>& arr, long long size, long long index) {
  long long smallest = index;
  long long left = 2 * index + 1;
  long long right = 2 * index + 2;

  if (left < size && arr[left] < arr[smallest]) {
    smallest = left;
  }
  if (right < size && arr[right] < arr[smallest]) {
    smallest = right;
  }
  if (smallest != index) {
    std::swap(arr[index], arr[smallest]);
    heapify(arr, size, smallest);
  }
}

// 构建最小堆
void build_heap(std::vector<long long>& arr) {
  long long n = arr.size();
  for (long long i = n / 2 - 1; i >= 0; --i) {
    heapify(arr, n, i);
  }
}

// --- Top-K 算法 (用于最后合并阶段) ---
std::vector<long long> topK(const std::vector<long long>& data, long long K) {
  if (data.empty() || K <= 0) {
    return {};
  }
  // 如果候选数不足K个，直接返回所有候选数
  if (data.size() <= static_cast<size_t>(K)) {
    return data;
  }
  std::vector<long long> heap(data.begin(), data.begin() + K);
  build_heap(heap);

  for (size_t i = K; i < data.size(); ++i) {
    if (data[i] > heap[0]) {
      heap[0] = data[i];
      heapify(heap, K, 0);
    }
  }
  return heap;
}

// --- 文件和多线程相关函数 ---

// 获取文件大小
long long get_file_size(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    throw std::runtime_error("Error opening file: " + filename);
  }
  return file.tellg();
}

// 线程工作函数：在文件的一个分块中寻找 Top-K
std::vector<long long> find_topK_in_chunk(const std::string& filename,
                                          long long start_pos,
                                          long long end_pos, long long K) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "线程错误: 无法打开文件 " << filename << std::endl;
    return {};
  }
  file.seekg(start_pos);

  // 如果不是文件开头，为避免读到半截数字，丢弃第一行
  if (start_pos != 0) {
    std::string dummy_line;
    std::getline(file, dummy_line);
  }

  std::vector<long long> heap;
  heap.reserve(K);

  std::string line;
  // 循环读取，直到当前文件指针超过块的结束位置
  while (static_cast<long long>(file.tellg()) < end_pos && file.tellg() != -1 &&
         std::getline(file, line)) {
    try {
      long long num = std::stoll(line);
      if (heap.size() < static_cast<size_t>(K)) {
        heap.push_back(num);
        if (heap.size() == static_cast<size_t>(K)) {
          build_heap(heap);
        }
      } else if (num > heap[0]) {
        heap[0] = num;
        heapify(heap, K, 0);
      }
    } catch (const std::invalid_argument&) {
      // 忽略无效行
    } catch (const std::out_of_range&) {
      // 忽略超出范围的数字
    }
  }
  return heap;
}

// --- 主函数 ---
int main(int argc, char* argv[]) {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  if (argc != 3) {
    std::cerr << "用法: " << argv[0] << " <文件名> <K值>" << std::endl;
    return 1;
  }

  try {
    const std::string FILENAME = argv[1];
    long long K = 0;
    try {
      K = std::stoll(argv[2]);
    } catch (const std::exception& e) {
      std::cerr << "错误: K值无效。请输入一个有效的数字。" << std::endl;
      return 1;
    }

    if (K <= 0) {
      std::cerr << "错误: K值必须是一个正整数。" << std::endl;
      return 1;
    }

    const int NUM_THREADS =
        std::thread::hardware_concurrency();  // 使用硬件支持的并发线程数

    std::cout << "正在处理文件 '" << FILENAME << "', 使用 " << NUM_THREADS
              << " 个线程查找最大的 " << K << " 个数。" << std::endl;

    // 1. 文件分块
    long long file_size = get_file_size(FILENAME);
    if (file_size == 0) {
      std::cerr << "文件为空或不存在。" << std::endl;
      return 1;
    }
    long long chunk_size = file_size / NUM_THREADS;
    std::vector<std::pair<long long, long long>> chunks;
    long long current_pos = 0;
    std::ifstream file_for_chunking(FILENAME);  // 优化：只打开一次文件用于分块

    for (int i = 0; i < NUM_THREADS; ++i) {
      long long start = current_pos;
      long long end = (i == NUM_THREADS - 1) ? file_size : start + chunk_size;

      // 调整end位置，确保它落在换行符之后，避免截断
      if (end < file_size) {
        file_for_chunking.seekg(end);
        std::string dummy;
        std::getline(file_for_chunking, dummy);  // 读取到行尾
        end = file_for_chunking.tellg();
        if (end == -1) {  // 到达文件末尾
          end = file_size;
        }
      }

      chunks.emplace_back(start, end);
      current_pos = end;
      if (current_pos >= file_size) {
        break;  // 如果分块已经覆盖整个文件，则提前结束
      }
    }
    file_for_chunking.close();  // 关闭文件

    // 2. 启动线程，异步计算每个分块的 Top-K
    std::vector<std::future<std::vector<long long>>> futures;
    futures.reserve(chunks.size());
    for (const auto& chunk : chunks) {
      futures.push_back(std::async(std::launch::async, find_topK_in_chunk,
                                   FILENAME, chunk.first, chunk.second, K));
    }

    // 3. 收集所有局部 Top-K 结果
    std::vector<long long> final_candidates;
    for (auto& f : futures) {
      auto partial_result = f.get();
      final_candidates.insert(final_candidates.end(), partial_result.begin(),
                              partial_result.end());
    }
    std::cout << "从所有线程收集到 " << final_candidates.size()
              << " 个候选数字。" << std::endl;

    // 4. 从候选者中找出最终的全局 Top-K
    std::vector<long long> final_result_heap = topK(final_candidates, K);

    // 5. 排序并保存结果到文件
    std::sort(final_result_heap.begin(), final_result_heap.end(),
              std::greater<long long>());

    const std::string OUTPUT_FILENAME = "answer.txt";
    std::ofstream answer_file(OUTPUT_FILENAME);
    if (!answer_file.is_open()) {
      std::cerr << "错误: 无法创建答案文件 " << OUTPUT_FILENAME << std::endl;
    } else {
      for (const auto& num : final_result_heap) {
        answer_file << num << "\n";
      }
      std::cout << "\n成功！最终最大的 " << final_result_heap.size()
                << " 个数已保存到文件 '" << OUTPUT_FILENAME << "' 中。"
                << std::endl;
    }
  } catch (const std::exception& e) {
    std::cerr << "发生严重错误: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
