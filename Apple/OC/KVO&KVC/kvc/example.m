#import <Foundation/Foundation.h>

@interface Person : NSObject {
  // 注意：这个 ivar 没有对应的 @property
  NSString *name;
}

@property(nonatomic, assign) NSInteger age;
@property(nonatomic, copy) NSString *city;

@end

@implementation Person
@end

int main() {
  @autoreleasepool {
    Person *p = [[Person alloc] init];
    [p setValue:@"小明" forKey:@"name"];
    // kvc查找顺序为：_name、_isName、nam、isName

    // 用 KVC 给有 property 的属性赋值
    [p setValue:@20 forKey:@"age"];
    [p setValue:@"北京" forKey:@"city"];

    // 读取属性
    NSLog(@"name = %@", [p valueForKey:@"name"]);
    NSLog(@"age  = %@", [p valueForKey:@"age"]);
    NSLog(@"city = %@", [p valueForKey:@"city"]);

    // 4. KeyPath 示例（假设 person 里再嵌套一层就可以用
    // keyPath，这里先感受语法） [p setValue:@"海淀"
    // forKeyPath:@"address.district"];

    return 0;
  }
}
