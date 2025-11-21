#import <Foundation/Foundation.h>

@interface DataProcessor : NSObject
// (id)object：(参数类型)变量名
// (void)processObject：(返回类型)方法名
- (void)processObject:(id)object;
@end

@implementation DataProcessor
- (void)processObject:(id)object {
  NSLog(@"object类型:%@", [object class]);
}
@end


int main() {
    DataProcessor* processor = [[DataProcessor alloc] init];
    [processor processObject:@"Hello"];
}