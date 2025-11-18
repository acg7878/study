#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

using namespace std;

vector<int> generateRandomData(int count) {
    vector<int> data(count);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-1000000000, 1000000000);
    for (int i = 0; i < count; ++i) {
        data[i] = dis(gen);
    }
    return data;
}

vector<int> topKWithMinHeap(const vector<int>& data, int K) {
    if (data.empty() || K <= 0 || K > data.size()) {
        return {};
    }
    // 小顶堆
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int i = 0; i < K; ++i) {
        minHeap.push(data[i]);
    }
    // 遍历剩余元素，比堆顶大则替换堆顶
    for (int i = K; i < data.size(); ++i) {
        if (data[i] > minHeap.top()) {
            minHeap.pop();
            minHeap.push(data[i]);
        }
    }
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    // 从大到小排序
    sort(result.rbegin(), result.rend());

    return result;
}

int main() {
    const int DATA_SIZE = 100000000;
    const int K = 50;
    cout << "Generating 1M random integers..." << endl;
    vector<int> data = generateRandomData(DATA_SIZE);
    cout << "Finding top " << K << " largest numbers..." << endl;
    cout << "Using std::priority_queue:" << endl;
    vector<int> topK_pq = topKWithMinHeap(data, K);
    cout << "The top " << K << " elements are: ";
    for (int val : topK_pq) {
        cout << val << " ";
    }
    cout << endl << endl;
    return 0;
}