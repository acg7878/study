#import <Foundation/Foundation.h>
#include <Foundation/NSObjCRuntime.h>

@protocol Vehicleprotocol <NSObject>

@required // 需要实现的方法
- (void)startEngine;
- (void)stopEngine;

@optional
- (void)turnOnRadio;

@end

@interface Car : NSObject <Vehicleprotocol>
@property(nonatomic, copy) NSString *name;
@end

@implementation Car
- (void)startEngine {
  NSLog(@"%@启动", self.name);
}
- (void)stopEngine {
  NSLog(@"%@停止", self.name);
}
@end

int main() {
  @autoreleasepool {
    Car *car = [[Car alloc] init];
    car.name = @"BMW";

    // id<VehicleProtocol> 能够隐藏具体类型，实现解耦
    // 还能限制访问权限，让编译器只知道协议里的方法
    id<Vehicleprotocol> vehicle = car;
    [vehicle startEngine];

    if ([vehicle respondsToSelector:@selector(turnOnRadio)]) {
      [vehicle turnOnRadio];
    } else {
      NSLog(@"该车未配备收音机");
    }
  }
  return 0;
}