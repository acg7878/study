#include <vector>
#include <queue>

using namespace std;

// 辅助结构体：存储当前元素的值、来源数组索引、以及在数组中的位置
struct Node {
    int val;
    int row; // 数组ID (第几个数组)
    int col; // 元素ID (该数组的第几个元素)

    // 重载小于运算符，定义最小堆的比较规则
    // 优先队列默认是大顶堆（less），为了让小的浮上来，我们需要反向定义
    // 或者让 priority_queue 使用 greater，这里采用重载 < 实现 "值大的优先级小"
    bool operator<(const Node& other) const {
        return val > other.val;
    }
};

class Solution {
public:
    /**
     * 合并 K 个升序数组
     * 时间复杂度: O(N * logK)，其中 N 是所有元素的总数，K 是数组的个数
     * 空间复杂度: O(K)，堆中最多维护 K 个元素
     */
    vector<int> mergeKArrays(vector<vector<int>>& arrays) {
        priority_queue<Node> pq;
        
        // 1. 初始化：将每个非空数组的第一个元素加入堆
        for (int i = 0; i < arrays.size(); ++i) {
            if (!arrays[i].empty()) {
                pq.push({arrays[i][0], i, 0});
            }
        }
        
        vector<int> result;
        
        // 2. 循环处理
        while (!pq.empty()) {
            // 取出当前最小的元素
            Node node = pq.top();
            pq.pop();
            
            result.push_back(node.val);
            
            // 3. 将该元素所在数组的"下一个元素"推入堆中
            if (node.col + 1 < arrays[node.row].size()) {
                pq.push({
                    arrays[node.row][node.col + 1], // 下一个值
                    node.row,                       // 依然是第 row 个数组
                    node.col + 1                    // 下标 + 1
                });
            }
        }
        
        return result;
    }
};