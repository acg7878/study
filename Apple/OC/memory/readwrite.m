#import <Foundation/Foundation.h>

@interface Person : NSObject
@property(readwrite) int age;
@property(readonly, copy) NSString *name;
@end

@implementation Person
@end

int main() { Person *p = [[Person alloc] init]; 
    p.age = 10;

    // 不可以修改
    // error: assignment to readonly property
    //p.name = @"123"; 
    
    NSLog(@"%@",p.name);
}