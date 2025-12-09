#import <Foundation/Foundation.h>
#include <stdio.h>
#import <objc/runtime.h>

@interface Person : NSObject
- (void)run; // 只有声明，没有实现
@end

@implementation Person

// 所有 Objective-C 方法底层都是 C 函数，默认带两个隐式参数：self 和 _cmd
void runIMP(id self, SEL _cmd) {
  printf("run!!");
}

+ (BOOL)resolveInstanceMethod:(SEL)sel {
  if (sel == @selector(run)) {
    Class cls = [self class];
    class_addMethod(cls, sel, (IMP)runIMP, "v@:");
    return YES;
  }
  return [super resolveInstanceMethod:sel];
}

@end

int main(int argc, const char *argv[]) {
  @autoreleasepool {
    Person *p = [[Person alloc] init];

    // 调用一个未实现的方法
    // 正常情况下这里会崩溃：unrecognized selector sent to instance
    // 但因为我们在 resolveInstanceMethod 中做了处理，它会成功运行
    [p run];
  }
  return 0;
}
