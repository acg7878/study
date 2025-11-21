#import <Foundation/Foundation.h>

// NSObject是所有类的基类，提供内存管理等功能
@interface Person : NSObject

@property(nonatomic, copy) NSString *name;
- (void)sayhello;

@end