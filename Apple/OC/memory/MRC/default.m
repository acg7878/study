#import <Foundation/Foundation.h>
#import <objc/runtime.h>
/*
    常见的特性编码：
    T@... -> 类型 (T@"NSString")
    &     -> retain (strong)
    C     -> copy
    W     -> weak
    (空)  -> assign (默认)
    R     -> readonly
    N     -> nonatomic
    V...  -> 实例变量名 (V_name)
    */
@interface Person : NSObject

// No 'assign', 'retain', or 'copy' attribute is specified - 'assign' is
// assumedclang(-Wobjc-property-no-attribute)
@property NSString *defaultProp;

@property(retain) NSString *retainProp;
@end

@implementation Person
@end

void printPropertyAttributes(Class cls, NSString *propName) {
  const char *cName = [propName UTF8String];
  objc_property_t property = class_getProperty(cls, cName);

  if (property) {
    const char *attributes = property_getAttributes(property);
    printf("属性 %s 的特性字符串: %s\n", cName, attributes);
  } else {
    printf("没找到属性 %s\n", cName);
  }
}

int main() {
  // 没有 '&'(retain) 也没有 'C'(copy)，说明是 assign
  printPropertyAttributes([Person class], @"defaultProp");
  printPropertyAttributes([Person class], @"retainProp");
  return 0;
}
