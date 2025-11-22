// 本质是函数指针
// SEL是方法名，IMP是执行代码的内存地址
#import <Foundation/Foundation.h>
#include <objc/objc.h>

// copy一段代码过来（）
@interface Person : NSObject
- (void)sayhello;
- (void)sayhelloTo:(NSString *)name;
+ (void)classMethod;
@end

@implementation Person
- (void)sayhello {
  printf("hello!");
}

- (void)sayhelloTo:(NSString *)name {
  NSLog(@"Hello,%@", name);
}

+ (void)classMethod {
  NSLog(@"this is a class method");
}
@end

int main() {
  @autoreleasepool {
    Person *person = [[Person alloc] init];

    // 直接调用 IMP（跳过消息发送的开销）
    // methodForSelector：找到函数地址
    IMP imp = [person methodForSelector:@selector(sayhello)];
    void (*func)(id, SEL) = (void *)imp;// id为调用者，SEL为方法名
    func(person, @selector(sayhello)); // func是函数指针名字，可以随便取


  }
}