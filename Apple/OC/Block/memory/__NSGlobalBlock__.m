#import <Foundation/Foundation.h>

int main() {
  @autoreleasepool {
    // 打印了一个常量字符串，字符串在全局数据区
    void (^myBlock)(void) = ^{
      NSLog(@"我是 Global Block");
    };
    NSLog(@"Block类型: %@", [myBlock class]);

    // 写法2
    // NSLog(@"%@", [^{
    //   NSLog(@"globalBlock");
    // } class]);
  }
  return 0;
}
