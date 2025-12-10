#import <CoreFoundation/CoreFoundation.h> // 引入 RunLoop 头文件
#import <Foundation/Foundation.h>

int main(int argc, const char *argv[]) {
  @autoreleasepool {
    NSLog(@"1--- isMain: %d", [NSThread isMainThread]);
    dispatch_async(dispatch_get_main_queue(), ^{
      NSLog(@"2-- isMain: %d", [NSThread isMainThread]);
      dispatch_async(dispatch_get_global_queue(0, 0), ^{
        NSLog(@"3-- isMain: %d", [NSThread isMainThread]);
        CFRunLoopStop(CFRunLoopGetMain());
      });
      NSLog(@"4-- isMain: %d", [NSThread isMainThread]);
    });
    NSLog(@"5--- isMain: %d", [NSThread isMainThread]);
    CFRunLoopRun();
  }
  return 0;
}