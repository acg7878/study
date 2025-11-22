#import <Foundation/Foundation.h>

@interface Dog : NSObject
@property(nonatomic, copy) NSString *name;
- (void)spark;
@end

@implementation Dog
- (void)spark {
    NSLog(@"汪汪汪");
}
@end

@interface Observer : NSObject
@end

@implementation Observer
- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary<NSKeyValueChangeKey, id> *)change
                       context:(void *)context {
  if ([keyPath isEqualToString:@"name"]) {
    NSLog(@"【KVO通知】监听到 %@ 的 name 属性变了！", object);
    NSLog(@"旧值: %@", change[NSKeyValueChangeOldKey]);
    NSLog(@"新值: %@", change[NSKeyValueChangeNewKey]);
  }
}
@end

int main() {
  Dog *dog = [[Dog alloc] init];
  Observer *observer = [[Observer alloc] init];
  [dog addObserver:observer
        forKeyPath:@"name"
           options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld
           context:nil];
  dog.name = @"布鲁斯";
  // 移除监听
  [dog removeObserver:observer forKeyPath:@"name"];
}