#import <Foundation/Foundation.h>
#include <stdio.h>

int main() {
  int a = 10;
  // f为float，否则默认为double
  float b = 3.14f;
  double pi = 3.1415;
  // BOOL 为 signed char
  BOOL flag = true;
  printf("%d\n", a);
  printf("%f\n", pi);
  printf("%d\n", flag);
}