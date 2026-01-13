#include <list>
#include <unordered_map>
#include <utility>
class LRUCache {
 private:
  int cap;
  std::list<std::pair<int, int>> lru_list;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> key_to_iter;

 public:
  LRUCache(int capacity) { cap = capacity; }

  int get(int key) {
    auto it = key_to_iter.find(key);
    if (it == key_to_iter.end()) {
      return -1;
    }
    auto iter = it->second;
    lru_list.splice(lru_list.begin(), lru_list, iter);
    return iter->second;
  }

  void put(int key, int value) {
    if (cap <= 0) {
      return;
    }

    auto it = key_to_iter.find(key);
    if (it != key_to_iter.end()) {
      auto list_iter = it->second;
      list_iter->second = value;
      lru_list.splice(lru_list.begin(), lru_list, list_iter);
      return;
    }

    if (lru_list.size() == cap) {
      auto expire = lru_list.back();
      key_to_iter.erase(expire.first);
      lru_list.pop_back();
    }

    lru_list.push_front({key, value});
    key_to_iter[key] = lru_list.begin();
  }
};

/**
     * Your LRUCache object will be instantiated and called as such:
     * LRUCache* obj = new LRUCache(capacity);
     * int param_1 = obj->get(key);
     * obj->put(key,value);
     */