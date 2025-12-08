#import <Foundation/Foundation.h>

void example() {
  NSOperationQueue *queue = [[NSOperationQueue alloc] init];
  queue.maxConcurrentOperationCount = 3;

  __block NSString *result1 = nil;
  __block NSString *result2 = nil;
  __block NSString *result3 = nil;

  NSBlockOperation *operation1 = [NSBlockOperation blockOperationWithBlock:^{
    result1 = @"数据1已下载";
    NSLog(@"任务1完成: %@", result1);
  }];

  NSBlockOperation *operation2 = [NSBlockOperation blockOperationWithBlock:^{
    result2 = @"数据2已下载";
    NSLog(@"任务2完成: %@", result2);
  }];

  NSBlockOperation *operation3 = [NSBlockOperation blockOperationWithBlock:^{
    result3 =
        [NSString stringWithFormat:@"合并结果: %@ + %@", result1, result2];
    NSLog(@"任务3完成: %@", result3);
  }];

  [operation3 addDependency:operation1];
  [operation3 addDependency:operation2];

  // 将任务添加到队列
  [queue addOperation:operation1];
  [queue addOperation:operation2];
  [queue addOperation:operation3];

  // 等待所有任务完成
  [queue waitUntilAllOperationsAreFinished];
  NSLog(@"示例完成\n");
}

int main() {
    example();
}