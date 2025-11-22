// 对栈block进行copy为堆block
// 对全局block进行copy，仍旧是全局block

#import <Foundation/Foundation.h>
int main() {
  // 注释的地方会打印__NSMallocBlock__
  // ARC环境自动拷贝，把 Block 赋值给一个强引用变量
  // 编译器就会自动把 Block 从栈上拷贝到堆上
  NSInteger num = 10;
  void (^printBlock)(void) = ^{
    NSLog(@"%ld", (long)num);
  };
  NSLog(@"类型:%@", [printBlock class]);
}