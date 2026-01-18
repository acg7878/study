

#include <atomic>

struct control_block_base {
  std::atomic<long> shared_owners{0};
  std::atomic<long> shared_weak_owners{0};

  control_block_base() = default;
  virtual ~control_block_base() = default;
  virtual void destroy_object() noexcept = 0;

  void add_shared() noexcept {
    shared_owners.fetch_add(1, std::memory_order_acq_rel);
  }

  bool release_shared() noexcept {
    if (shared_owners.fetch_sub(1, std::memory_order_acq_rel) == 1) {
      destroy_object();
      return true;
    }
    return false;
  }

  void add_weak() noexcept {
    shared_weak_owners.fetch_add(1, std::memory_order_acq_rel);
  }

  bool release_weak() noexcept {
    if (shared_weak_owners.fetch_sub(1, std::memory_order_acq_rel) == 1) {
      delete this;
      return true;
    }
    return false;
  }
};

template <typename T, typename Deleter>
struct control_block : control_block_base {
  T* ptr;
  Deleter d;
};