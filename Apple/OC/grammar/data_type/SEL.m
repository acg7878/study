// 选择器类型
#import <Foundation/Foundation.h>
#include <stdio.h>
// -：实例方法
// +：类方法
@interface Person: NSObject
- (void)sayhello;
- (void)sayhelloTo:(NSString*)name;
+ (void)classMethod;
@end

@implementation Person
- (void)sayhello {
    printf("hello!");
}

- (void)sayhelloTo:(NSString*)name {
    NSLog(@"Hello,%@",name);
}

+ (void)classMethod {
    NSLog(@"this is a class method");
}
@end

int main() {
    Person* person = [[Person alloc] init];

    SEL sel1 = @selector(sayhello);
    SEL sel2 = @selector(sayhelloTo:);
    SEL sel3 = @selector(classMethod);

    // 让person这个实例去执行sel1代表的方法
    [person performSelector:sel1];
    // "withObject:":带上参数,只能传递一个参数并且只能是对象
    [person performSelector:sel2 withObject:@"Tom"];
    [Person performSelector:sel3];
}