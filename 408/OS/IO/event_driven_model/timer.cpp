#include <sys/event.h>
#include <unistd.h>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>

using TimerCallback = std::function<void(int)>;

class EventLoop {
 private:
  int kq_fd;
  std::map<int, TimerCallback> callbacks;

 public:
  EventLoop() {
    kq_fd = kqueue();
    if (kq_fd == -1) {
      perror("create error!");
      exit(1);
    }
  }
  ~EventLoop() { close(kq_fd); }

  void add_timer(int timer_id, int ms, TimerCallback cb) {
    struct kevent kev;

    // &kev, ident(ID), filter(类型), flags(动作), fflags(特定标志), data(数据), udata(用户数据)
    // EVFILT_TIMER: 定时器过滤器
    // EV_ADD | EV_ENABLE: 添加并启用
    // NOTE_MSECONDS: 单位是毫秒 (macOS/FreeBSD 特有，Linux timerfd 不一样)
    EV_SET(&kev, timer_id, EVFILT_TIMER, EV_ADD | EV_ENABLE, 0, ms, NULL);

    if (kevent(kq_fd, &kev, 1, NULL, 0, NULL)) {
      perror("add error!");
      return;
    }
    callbacks[timer_id] = cb;
    std::cout << "[Loop] Added timer " << timer_id << " (" << ms << "ms)"
              << std::endl;
  }

  void run() {
    std::cout << "[Loop] Event loop started..." << std::endl;
    struct kevent events[10];  // 一次最多处理10个事件

    while (true) {
      int nev = kevent(kq_fd, NULL, 0, events, 10, NULL);

      if (nev == -1) {
        perror("kevent wait");
        break;
      }
      for (int i = 0; i < nev; i++) {
        struct kevent& ev = events[i];

        if (ev.filter == EVFILT_TIMER) {
          int id = (int)ev.ident;  // 获取 TimerID

          // 查找并执行回调
          if (callbacks.find(id) != callbacks.end()) {
            callbacks[id](id);
          }
        }
      }
    }
  }
};

int main() {
  EventLoop loop;

  // 注册定时器 1: 每 1000ms 触发一次
  loop.add_timer(1, 1000, [](int id) {
    std::cout << "Timer " << id << " tick! (1s)" << std::endl;
  });

  // 注册定时器 2: 每 3000ms 触发一次
  loop.add_timer(2, 3000, [](int id) {
    std::cout << "Timer " << id << " tick! (3s)" << std::endl;
  });

  // 启动循环
  loop.run();

  return 0;
}