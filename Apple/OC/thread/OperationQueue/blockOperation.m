#import <Foundation/Foundation.h>
#include <Foundation/NSObjCRuntime.h>

int main() {
    NSBlockOperation *operation = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"Hello World!");
    }];
    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
    [queue addOperation:operation];
    [queue addOperationWithBlock:^{
        NSLog(@"addOperationWithBlock!");
    }];
    [queue waitUntilAllOperationsAreFinished];
}