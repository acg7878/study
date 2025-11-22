#import <Foundation/Foundation.h>

// 99%使用nonatomic

@interface BankAccount : NSObject
@property (atomic, copy) NSString *atomicString;
@property (nonatomic, copy) NSString *nonatomicString;
@end

@implementation BankAccount
@end

int main() {
    @autoreleasepool {
        BankAccount *account = [[BankAccount alloc] init];
        NSLog(@"开始测试 nonatomic (可能会 Crash)...");
        dispatch_group_t group = dispatch_group_create();
        dispatch_group_async(group, dispatch_get_global_queue(0, 0), ^{
            for (int i = 0; i < 100000; i++) {
                account.nonatomicString = [NSString stringWithFormat:@"NonAtomic - %d - 这是一个非常非常非常长的字符串用来增加CPU的负担让它更容易崩溃崩溃崩溃崩溃崩溃", i];
            }
        });
        dispatch_group_async(group, dispatch_get_global_queue(0, 0), ^{
            for (int i = 0; i < 100000; i++) {
                NSString *str = account.nonatomicString;
                if (str.length > 0) { /* 只读，不做事 */ }
            }
        });
        dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
        NSLog(@"nonatomic 测试结束 (如果能看到这行说明运气好没崩)");
    }
    return 0;
}

