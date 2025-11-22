#import <Foundation/Foundation.h>
#include <Foundation/NSObjCRuntime.h>

@interface CalculationManager : NSObject
- (void)calculateSum:(NSArray *)array;
@end

@implementation CalculationManager
- (void)calculateSum:(NSArray *)array {
  if (!array || array.count == 0) {
    return;
  }

  long long sum = 0;
  for (NSNumber *num in array) {
    int value = [num intValue];
    sum += value * value;
  }
  NSLog(@"结果为%lld",sum);
}
@end

int main() {
  NSArray *numbers = @[ @1, @2, @3, @4, @5 ];
  CalculationManager *manager = [[CalculationManager alloc] init];
  NSThread *thread = [[NSThread alloc] initWithTarget:manager
                                             selector:@selector(calculateSum:)
                                               object:numbers];
  thread.name = @"CalculatedThread";
  [thread start];
  
  // 让主线程睡 1 秒，等待子线程跑完
  [NSThread sleepForTimeInterval:1.0]; 
}