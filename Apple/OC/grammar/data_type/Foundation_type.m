#include <Foundation/Foundation.h>
// Foundation类型为引用类型

int main() {
  // @为字面量语法
  NSString *name = @"小猫";
  NSNumber *count = @(10);
  NSArray *array = @[ @1, @2, @3 ];
  NSDictionary *dict = @{@"name" : @"李四"};
  NSSet *set = [NSSet setWithObjects:@1, @2, nil];
  NSDate *now = [NSDate date];
  NSData *data = [@"test" dataUsingEncoding:NSUTF8StringEncoding];

  NSLog(@"%@",name);

}