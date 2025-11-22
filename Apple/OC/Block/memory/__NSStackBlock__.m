#import <Foundation/Foundation.h>

// 不使用外部变量并且未进行copy操作的block
// 为栈block

int main() {
  NSInteger num = 10;
  NSLog(@"%@", [^{
          NSLog(@"%ld", num);
        } class]);

  // 注释的地方会打印__NSMallocBlock__
  // ARC环境自动拷贝，把 Block 赋值给一个强引用变量
  // 编译器就会自动把 Block 从栈上拷贝到堆上
  void (^printBlock)(void) = ^{
      NSLog(@"%ld",(long)num);
  };
  NSLog(@"类型:%@",[printBlock class]);
  
}