#import <Foundation/Foundation.h>

void example1_dispatch_group() {
  dispatch_queue_t curQueue =
      dispatch_queue_create("com.example.cur", DISPATCH_QUEUE_CONCURRENT);
  dispatch_group_t group = dispatch_group_create();

  __block NSString *result1 = nil;
  __block NSString *result2 = nil;
  __block NSString *result3 = nil;

  dispatch_group_async(group, curQueue, ^{
    result1 = @"数据1已下载";
    NSLog(@"%@", result1);
  });
  dispatch_group_async(group, curQueue, ^{
    result2 = @"数据2已下载";
    NSLog(@"%@", result2);
  });

  dispatch_group_notify(group, curQueue, ^{
    result3 = [NSString stringWithFormat:@"%@%@",result1,result2];
    NSLog(@"%@",result3);
  });
  dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
    NSLog(@"所有任务完成\n");

}

int main() {
    example1_dispatch_group();
}