#import <Foundation/Foundation.h>

void example_chain() {
  NSLog(@"\n========== 示例3: 链式依赖 ==========");
  dispatch_queue_t queue =
      dispatch_queue_create("com.example.concurrent", DISPATCH_QUEUE_CONCURRENT);

  // 阶段1: 获取数据
  dispatch_group_t group1 = dispatch_group_create();
  __block NSString *stage1Result = nil;

  dispatch_group_async(group1, queue, ^{
    sleep(1);
    stage1Result = @"阶段1数据";
    NSLog(@"阶段1完成: %@", stage1Result);
  });

  // 阶段2: 依赖阶段1，处理数据
  dispatch_group_t group2 = dispatch_group_create();
  __block NSString *stage2Result = nil;

  dispatch_group_notify(group1, queue, ^{
    dispatch_group_async(group2, queue, ^{
      sleep(1);
      stage2Result = [NSString stringWithFormat:@"处理后的%@", stage1Result];
      NSLog(@"阶段2完成: %@", stage2Result);
    });
  });

  // 阶段3: 依赖阶段2，最终处理
  dispatch_group_notify(group2, queue, ^{
    NSLog(@"阶段3完成: 最终结果 - %@", stage2Result);
  });

  dispatch_group_wait(group1, DISPATCH_TIME_FOREVER);
  dispatch_group_wait(group2, DISPATCH_TIME_FOREVER);
  NSLog(@"示例3完成\n");
}

int main() {
    example_chain();
}