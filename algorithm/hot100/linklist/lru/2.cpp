#include <list>
#include <unordered_map>
#include <utility>
class LRUCache {
 public:
  int capacity;
  std::list<std::pair<int, int>> lru_list;  // pair: key,value;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> hashtable;

  LRUCache(int capacity) { this->capacity = capacity; }

  int get(int key) {
    auto it = hashtable.find(key);
    if (it == hashtable.end()) {
      return -1;
    }
    auto iter = it->second;
    lru_list.splice(lru_list.begin(), lru_list, iter);
    return iter->second;
  }

  void put(int key, int value) {
    auto it = hashtable.find(key);
    if (it == hashtable.end()) {
      // 判断满了没有
      if (capacity == lru_list.size()) {
        // 满了，淘汰一个
        auto node = lru_list.back();
        hashtable.erase(node.first);
        lru_list.pop_back();
      }
      // 没有在lru内，插入到队头
      lru_list.push_front({key, value});
      hashtable[key] = lru_list.begin();
      return;
    }

    // 在里面，替换一下值，并移动到队头
    auto iter = it->second;
    iter->second = value;
    lru_list.splice(lru_list.begin(), lru_list, iter);
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */