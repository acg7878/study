#include <stdio.h>

int d = 40;

int main() {
  int a = 10;
  static int b = 20;
  __block int c = 30;
  printf("before a:%d\n", a);
  printf("before b:%d\n", b);
  printf("before c:%d\n", c);
  printf("before d:%d\n", d);

  // 局部变量的捕获是值捕获
  // 静态的是指针捕获
  // 全局变量直接取值
  void (^blk)(void) = ^{
    // 捕获是发生在定义的时刻，所以后面的修改无效了
    printf("after a:%d\n", a);
    printf("after b:%d\n", b);
    printf("after c:%d\n", c);
    printf("after d:%d\n", d);

  };
  a += 1;
  b += 1;
  c += 1;
  d += 1;
  blk();
}