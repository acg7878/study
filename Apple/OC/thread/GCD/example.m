#import <Foundation/Foundation.h>
#import <stdatomic.h> // C11 原子操作库

int main() {
  @autoreleasepool {
    int count = 1000000;
    NSMutableArray *numbers = [NSMutableArray arrayWithCapacity:count];
    for (int i = 0; i < count; i++) {
      [numbers addObject:@(2)];
    }
    NSLog(@"开始计算 %d 个数字的平方和...", count);
    NSDate *startDate = [NSDate date];

    // 定义一个原子变量 sum (线程安全，不用加锁，性能极高)
    // 如果不用 atomic，就得用 NSLock 或 @synchronized，会慢很多
    __block _Atomic long long sum = 0;

    // 3. 使用 dispatch_apply 进行并发遍历
    // 它可以自动利用所有 CPU 核心，并发执行
    // count: 遍历次数
    // queue: 必须是并发队列
    dispatch_apply(count, dispatch_get_global_queue(0, 0), ^(size_t index) {
      // index是start到end的每一个数
      int value = [numbers[index] intValue];
      // 这里的 += 是原子操作，多线程同时写也没问题
      sum += (long long)value * value;
    });

    NSDate *endDate = [NSDate date];
    NSLog(@"计算完成！结果: %lld", sum);
    NSLog(@"耗时: %f 秒", [endDate timeIntervalSinceDate:startDate]);
  }
  return 0;
}
