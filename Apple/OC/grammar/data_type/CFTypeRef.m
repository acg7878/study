// CFTypeRef 是 Core Foundation (CF) 框架中所有对象的“通用类型”
// 类似于 Objective-C 中的 id
// 本质是void*，或者说C语言版本的id
#import <CoreFoundation/CoreFoundation.h>
#import <Foundation/Foundation.h>
int main() {
  CFStringRef cfString =
      CFStringCreateWithCString(NULL, "Hello CFTypeRef", kCFStringEncodingUTF8);
  CFShow(cfString);
  // 免费桥接
  NSString *ocString = (__bridge NSString *)cfString;
  NSLog(@"Converted to OC: %@", ocString);
  CFRelease(cfString);
}
