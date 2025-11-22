#import <Foundation/Foundation.h>

@interface Person : NSObject
@property(strong) NSString *SName;
@property(copy) NSString *CName;
@property(weak) id weakObject;

// 用于非对象的基本数据类型
// 用于对象的话死后不会置空，变成野指针
@property(assign) NSInteger age; 
@end

@implementation Person
@end

int main() {
  @autoreleasepool {
    Person *person = [[Person alloc] init];
    NSMutableString *originStr = [NSMutableString stringWithString:@"Original"];
    person.SName = originStr;
    person.CName = originStr;
    [originStr appendString:@"->Changed"];
    NSLog(@"Strong属性: %@", person.SName);
    NSLog(@"Copy属性: %@", person.CName);

    {
      NSObject *temp = [[NSObject alloc] init];
      person.weakObject = temp;
      NSLog(@"temp对象存在，weakObject为%@", person.weakObject);
    }
    // weak标记的属性，销毁后指向nil
    NSLog(@"temp对象销毁，weakObject为%@", person.weakObject);
  }
}