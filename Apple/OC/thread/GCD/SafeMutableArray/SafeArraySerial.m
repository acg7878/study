#import <Foundation/Foundation.h>

// 方案一：读写都走串行队列
// 特点：实现简单，无并发冲突，但读操作会被写操作阻塞，且读操作之间也无法并发，性能较低。

@interface SafeArraySerial : NSObject
@property (nonatomic, strong) NSMutableArray *array;
@property (nonatomic, strong) dispatch_queue_t queue;

- (void)addObject:(id)obj;
- (id)objectAtIndex:(NSUInteger)index;
@end

@implementation SafeArraySerial

- (instancetype)init {
    if (self = [super init]) {
        _array = [NSMutableArray array];
        // 1. 创建串行队列 (DISPATCH_QUEUE_SERIAL)
        _queue = dispatch_queue_create("com.study.SafeArraySerial", DISPATCH_QUEUE_SERIAL);
    }
    return self;
}

// 写操作：串行队列 + 异步 (async)
// 使用 async 不会阻塞当前调用线程，但在队列中依然是顺序执行，保证安全
- (void)addObject:(id)obj {
    dispatch_async(self.queue, ^{
        [self.array addObject:obj];
        NSLog(@"写入: %@", obj);
    });
}

// 读操作：串行队列 + 同步 (sync)
// 使用 sync 因为需要立即返回数据。读操作会在队列中排队，无法并发。
- (id)objectAtIndex:(NSUInteger)index {
    __block id obj = nil;
    dispatch_sync(self.queue, ^{
        if (index < self.array.count) {
            obj = self.array[index];
        }
        NSLog(@"读取: 索引 %lu -> %@", (unsigned long)index, obj);
    });
    return obj;
}

@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSLog(@"--- 方案一：串行队列 (读写均串行) ---");
        SafeArraySerial *safeArray = [[SafeArraySerial alloc] init];
        
        // 模拟多线程环境
        dispatch_queue_t testQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        
        // 模拟并发写入
        for (int i = 0; i < 5; i++) {
            dispatch_async(testQueue, ^{
                [safeArray addObject:@(i)];
            });
        }
        
        // 模拟并发读取
        for (int i = 0; i < 5; i++) {
            dispatch_async(testQueue, ^{
                // 稍微延时确保有数据可读
                usleep(1000);
                [safeArray objectAtIndex:i];
            });
        }
        
        sleep(2); // 等待异步任务完成
        NSLog(@"最终数组个数: %lu", (unsigned long)safeArray.array.count);
    }
    return 0;
}

