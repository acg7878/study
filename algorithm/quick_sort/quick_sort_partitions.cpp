#include <iostream>
#include <vector>
#include <utility>
#include <string>

// 辅助函数，用于打印向量内容
void print_vector(const std::vector<int>& arr, const std::string& label) {
    std::cout << label << ": ";
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// --- 策略一: Lomuto 分区 ---
// 将等于 pivot 的元素全部分到左侧（小于等于区域）
// 缺点: 遇到大量重复元素时，分区会极度不平衡，导致性能退化到 O(n^2)
int lomuto_partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为基准
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) { // 小于或等于 pivot 的都换到左边
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[i], arr[high]);
    return i;
}

void quick_sort_lomuto(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = lomuto_partition(arr, low, high);
        quick_sort_lomuto(arr, low, p - 1);
        quick_sort_lomuto(arr, p + 1, high);
    }
}

// --- 策略二: Hoare 分区 ---
// 原始的快排分区方案，左右指针相向移动
// 优点: 通常比 Lomuto 更高效，交换次数更少，能较好地处理重复元素
// 注意: 它不保证返回的分割点就是 pivot 的最终位置
int hoare_partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[low]; // 选择第一个元素作为基准
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);
        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }
        std::swap(arr[i], arr[j]);
    }
}

void quick_sort_hoare(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = hoare_partition(arr, low, high);
        quick_sort_hoare(arr, low, p);
        quick_sort_hoare(arr, p + 1, high);
    }
}

// --- 策略三: 三路分区 (荷兰国旗问题) ---
// 将数组分为 < pivot, == pivot, > pivot 三个部分
// 优点: 处理重复元素的最佳方式，后续递归可忽略中间 "==" 的部分，避免 O(n^2) 退化
void quick_sort_3_way(std::vector<int>& arr, int low, int high) {
    if (low >= high) {
        return;
    }
    int pivot = arr[low];
    int lt = low;     // 小于 pivot 的区域边界
    int gt = high;    // 大于 pivot 的区域边界
    int i = low + 1;  // 当前遍历的元素

    while (i <= gt) {
        if (arr[i] < pivot) {
            std::swap(arr[lt], arr[i]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            std::swap(arr[i], arr[gt]);
            gt--;
        } else { // arr[i] == pivot
            i++;
        }
    }

    quick_sort_3_way(arr, low, lt - 1);
    quick_sort_3_way(arr, gt + 1, high);
}


int main() {
    // 使用一个包含大量重复元素的数组来测试
    std::vector<int> test_arr = {5, 8, 5, 2, 9, 5, 6, 5, 1, 5, 0, 5};

    // 1. 测试 Lomuto 分区
    std::vector<int> arr1 = test_arr;
    std::cout << "--- Lomuto Partition ---" << std::endl;
    print_vector(arr1, "Original");
    quick_sort_lomuto(arr1, 0, arr1.size() - 1);
    print_vector(arr1, "Sorted  ");
    std::cout << std::endl;

    // 2. 测试 Hoare 分区
    std::vector<int> arr2 = test_arr;
    std::cout << "--- Hoare Partition ---" << std::endl;
    print_vector(arr2, "Original");
    quick_sort_hoare(arr2, 0, arr2.size() - 1);
    print_vector(arr2, "Sorted  ");
    std::cout << std::endl;

    // 3. 测试三路分区
    std::vector<int> arr3 = test_arr;
    std::cout << "--- 3-Way Partition ---" << std::endl;
    print_vector(arr3, "Original");
    quick_sort_3_way(arr3, 0, arr3.size() - 1);
    print_vector(arr3, "Sorted  ");
    std::cout << std::endl;

    return 0;
}
