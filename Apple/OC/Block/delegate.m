#import <Foundation/Foundation.h>

/**
 * block 代理实现：
 * - Worker 对外暴露两个 block 属性，调用方把“完成/失败”要做的事以 block 形式传进来。
 * - Worker 内部在合适时机执行这些 block，效果与 delegate 回调一致。
 */
@interface Worker : NSObject
/// 任务成功时回调
@property (nonatomic, copy) void (^onSuccess)(NSString *msg);
/// 任务失败时回调
@property (nonatomic, copy) void (^onFailure)(NSError *error);

- (void)startWorkShouldSucceed:(BOOL)ok;
@end

@implementation Worker

- (void)xstartWorkShouldSucceed:(BOOL)ok {
    if (ok) {
        if (self.onSuccess) {
            self.onSuccess(@"任务完成，数据已保存");
        }
    } else {
        if (self.onFailure) {
            NSError *err = [NSError errorWithDomain:@"demo.worker"
                                               code:1001
                                           userInfo:@{NSLocalizedDescriptionKey: @"任务失败，网络异常"}];
            self.onFailure(err);
        }
    }
}

@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        Worker *w = [Worker new];

        // 注意避免循环引用，通常持有者用 weakSelf
        __weak typeof(w) weakWorker = w;
        w.onSuccess = ^(NSString *msg) {
            // 这里示例直接用 weakWorker，真实场景常用 weakSelf 指向控制器
            NSLog(@"[成功] %@ (worker=%@)", msg, weakWorker);
        };
        w.onFailure = ^(NSError *error) {
            NSLog(@"[失败] %@", error.localizedDescription);
        };

        [w startWorkShouldSucceed:YES];
        [w startWorkShouldSucceed:NO];
    }
    return 0;
}
