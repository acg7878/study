#import <Foundation/Foundation.h>
#include <Foundation/NSObjCRuntime.h>

int main() {
  dispatch_block_t task = ^{
    NSLog(@"无效打印");
  };

  dispatch_queue_t queue =
      dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);

  dispatch_sync(queue, task);
}