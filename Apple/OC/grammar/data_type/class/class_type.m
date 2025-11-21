#import <Foundation/Foundation.h>
#import "Person.h"

int main() {
    @autoreleasepool {
        Class person;
        person = [Person class];
        NSLog(@"%@",person);
    }
}