#include <Foundation/Foundation.h>
#include <Foundation/NSObjCRuntime.h>
#include <MacTypes.h>
#import <objc/message.h>
@interface Dog : NSObject
- (void)spark;
- (void)eat:(NSString *)food;
@end

@implementation Dog
- (void)spark {
  NSLog(@"汪汪汪！！！");
}
- (void)eat:(NSString *)food {
  NSLog(@"小狗吃了%@", food);
}
@end

int main() {
    @autoreleasepool {
        Dog *dog = [[Dog alloc]init];
        [dog spark];
        [dog eat:@"战斧牛排"];

        // 给nil发消息不会崩溃
        Dog *nilDog = nil;
        [nilDog spark];

        // 运行时决议
        // [dog spark]; 这行代码在编译后，本质上变成了下面的 C 语言调用：
        // 需要引入 #import <objc/message.h>
        ((void (*)(id, SEL))objc_msgSend)(dog, @selector(spark));
        
    }
}