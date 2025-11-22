#import <Foundation/Foundation.h>
#include <string.h>

@interface Person : NSObject
@property(nonatomic, copy) NSString *name;
- (void)changeName;
@end

@implementation Person
- (void)changeName {
  NSString *oldName = self.name;
  // 系统生成的setter其实会添加这两个，绕过的话只能自己添加了
  [self willChangeValueForKey:@"name"];
  _name = @"新名字";
  [self didChangeValueForKey:@"name"];
}

// 必须实现这个方法才能收到通知
- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary<NSKeyValueChangeKey, id> *)change
                       context:(void *)context {
  NSLog(@"收到通知: name 从 %@ 变成了 %@", change[NSKeyValueChangeOldKey],
        change[NSKeyValueChangeNewKey]);
}
@end

int main() {
  Person *person = [[Person alloc] init];
  [person
      addObserver:person
       forKeyPath:@"name"
          options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld
          context:NULL];
  [person changeName];
}