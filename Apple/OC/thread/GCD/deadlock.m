#import <Foundation/Foundation.h>

int main() {
  @autoreleasepool {
    NSLog(@"1. 任务开始");

    // 死锁核心代码
    // 场景：在主线程中，往主队列里同步派发任务
    dispatch_sync(dispatch_get_main_queue(), ^{
      NSLog(@"2. 我永远不会被打印");
    });

    NSLog(@"3. 任务结束");

    // 主队列等着 main 跑完（或者让出控制权）才能去跑 Block。
    // Block 等着 主队列 调度它才能跑。
    // main 等着 Block 跑完才能往下跑
  }
  return 0;
}
