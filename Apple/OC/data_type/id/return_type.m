#import <Foundation/Foundation.h>

@interface ReturnTypeObject : NSObject
- (id)returnTypeMethod:(id)object;
@end

@implementation ReturnTypeObject
- (id)returnTypeMethod:(id)object {
    return object;
}
@end

int main() {
    ReturnTypeObject* object = [[ReturnTypeObject alloc] init];
    id temp = [object returnTypeMethod:[NSString class]];
    NSLog(@"Returned object: %@", temp);
}