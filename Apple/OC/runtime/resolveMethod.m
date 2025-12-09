#import <Foundation/Foundation.h>
#import <objc/runtime.h>

@interface Person : NSObject
- (void)run; // 只有声明，没有实现
@end

@implementation Person

// 所有 Objective-C 方法底层都是 C 函数，默认带两个隐式参数：self 和 _cmd
void runIMP(id self, SEL _cmd) {
  NSLog(@"动态添加的 run 方法被调用了！");
  NSLog(@"对象: %@", self);
  NSLog(@"方法: %@", NSStringFromSelector(_cmd));
}

+ (BOOL)resolveInstanceMethod:(SEL)sel {
  NSLog(@"⚠️ 发现未实现的方法: %@", NSStringFromSelector(sel));

  // 判断是不是要处理的那个方法
  if (sel == @selector(run)) {

    // 获取类对象
    Class cls = [self class];

    // 动态添加方法
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
