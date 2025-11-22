#import "Person.h"
#import <Foundation/Foundation.h>
#import <objc/runtime.h>

int main() {
  @autoreleasepool {
    Class person = [Person class];
    Class strClass = [NSString class];
    NSString *str = @"Hello";
    Class strClass2 = object_getClass(str);
    Class strClass3 = object_getClass([NSString class]);

    NSLog(@"person: %@", person);
    NSLog(@"strClass: %@", strClass);
    NSLog(@"strClass2: %@", strClass2);
    NSLog(@"strClass3: %@", strClass3);
  }
}