#import <Foundation/Foundation.h>

// 多个Notify
void example2() {
  dispatch_queue_t queue = dispatch_queue_create("com.example.concurrent",
                                                 DISPATCH_QUEUE_CONCURRENT);
  dispatch_group_t group = dispatch_group_create();

  __block NSString *data = nil;

  dispatch_group_async(group, queue, ^{
    sleep(1);
    data = @"基础数据";
    NSLog(@"基础任务完成: %@", data);
  });

  // 可以注册多个 notify，它们都会在组内所有任务完成后执行
  dispatch_group_notify(group, queue, ^{
    NSLog(@"回调1: 处理数据 - %@", data);
  });

  dispatch_group_notify(group, queue, ^{
    NSLog(@"回调2: 保存数据 - %@", data);
  });

  dispatch_group_notify(group, queue, ^{
    NSLog(@"回调3: 通知用户 - %@", data);
  });

  dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
  NSLog(@"示例2完成\n");
}

int main() {
    example2();
}