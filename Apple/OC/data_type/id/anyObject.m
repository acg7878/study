#import <Foundation/Foundation.h>

// id可以声明变量，接受任意对象

int main() {
    id object = @"123";
    NSLog(@"object:%@",[object class]);
}