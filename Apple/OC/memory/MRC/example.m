#import <Foundation/Foundation.h>
#include <Foundation/NSObjCRuntime.h>

@interface Dog : NSObject
@end

@implementation Dog
- (void)dealloc {
    NSLog(@"狗狗死亡");
    [super dealloc];
}
@end

@interface Owner:NSObject {
    Dog* dog;
}
- (void)setDog:(Dog*)dog;
- (Dog *)dog;
@end

@implementation Owner 
- (void)setDog:(Dog *)newDog {
    if (self.dog != newDog) {
        [self.dog release];
        self.dog = [newDog retain];
    }
}

-(Dog*)dog {
    return self.dog;
}

- (void)dealloc {
    NSLog(@"主人将死，宠物放生");
    [dog release];
    [super dealloc];
}
@end

int main() {
    Owner* person = [[Owner alloc]init];
    Dog* dog = [[Dog alloc]init];
    [person setDog:dog];
    [dog release]; // 流浪狗-1

    [person release];
}