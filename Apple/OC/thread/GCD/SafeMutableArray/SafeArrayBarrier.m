#import <Foundation/Foundation.h>

// 方案二：读走并发队列 + 写走栅栏函数 (推荐)
// 特点：读操作可以并发执行（性能高），写操作使用栅栏函数确保独占（安全）。

@interface SafeArrayBarrier : NSObject
@property (nonatomic, strong) NSMutableArray *array;
@property (nonatomic, strong) dispatch_queue_t queue;

- (void)addObject:(id)obj;
- (id)objectAtIndex:(NSUInteger)index;
@end

@implementation SafeArrayBarrier

- (instancetype)init {
    if (self = [super init]) {
        _array = [NSMutableArray array];
        // 1. 创建并发队列 (DISPATCH_QUEUE_CONCURRENT)
        // 注意：栅栏函数 barrier 必须配合自定义的并发队列使用，不能使用全局并发队列
        _queue = dispatch_queue_create("com.study.SafeArrayBarrier", DISPATCH_QUEUE_CONCURRENT);
    }
    return self;
}

// 写操作：并发队列 + 栅栏函数 (barrier_async)
// 栅栏函数会等待队列中已有的任务（如之前的读）执行完毕后，单独执行栅栏块，
// 且栅栏块执行时，队列中不会执行其他任务（即独占），执行完后恢复并发。
- (void)addObject:(id)obj {
    dispatch_barrier_async(self.queue, ^{
        [self.array addObject:obj];
        NSLog(@"[Barrier] 写入: %@", obj);
    });
}

// 读操作：并发队列 + 同步 (sync)
// 多个读操作可以在并发队列中同时执行，互不阻塞，提高了读取效率。
- (id)objectAtIndex:(NSUInteger)index {
    __block id obj = nil;
    dispatch_sync(self.queue, ^{
        if (index < self.array.count) {
            obj = self.array[index];
        }
        // NSLog(@"读取: 索引 %lu -> %@", (unsigned long)index, obj); // 注释掉避免日志过多影响观察并发
    });
    return obj;
}

@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSLog(@"--- 方案二：并发队列 + 栅栏函数 (多读单写) ---");
        SafeArrayBarrier *safeArray = [[SafeArrayBarrier alloc] init];
        
        dispatch_queue_t testQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        
        // 模拟：先有一批读写混合的操作
        for (int i = 0; i < 5; i++) {
            dispatch_async(testQueue, ^{
                [safeArray addObject:@(i)];
            });
        }
        
        for (int i = 0; i < 10; i++) {
            dispatch_async(testQueue, ^{
                id result = [safeArray objectAtIndex:0];
                NSLog(@"并发读取: %@", result);
            });
        }
        
        sleep(2);
        NSLog(@"最终数组个数: %lu", (unsigned long)safeArray.array.count);
    }
    return 0;
}

