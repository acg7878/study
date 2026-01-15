#import <Foundation/Foundation.h>

int main() {
  @autoreleasepool {
    // create operation queue
    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
    NSBlockOperation *operation = [[NSBlockOperation alloc] init];
    [operation addExecutionBlock:^{
      NSLog(@"Hello, world!");
    }];
    [queue addOperation:operation];
    [queue waitUntilAllOperationsAreFinished];
  }
}
