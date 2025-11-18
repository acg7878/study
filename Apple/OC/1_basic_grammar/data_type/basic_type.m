//
//  basic_type.m
//  Objective-C 基本数据类型示例
//
//  Created for learning Objective-C
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        NSLog(@"========== Objective-C 基本数据类型 ==========");
        // ========== 1. 整数类型 ==========
        NSLog(@"\n--- 整数类型 ---");
        // 有符号整数
        int integerValue = 42;
        short shortValue = 32767;
        long longValue = 2147483647L;
        long long longLongValue = 9223372036854775807LL;
        
        // 无符号整数
        unsigned int unsignedInt = 100;
        unsigned short unsignedShort = 65535;
        unsigned long unsignedLong = 4294967295UL;
        unsigned long long unsignedLongLong = 18446744073709551615ULL;
        
        NSLog(@"int: %d", integerValue);
        NSLog(@"short: %hd", shortValue);
        NSLog(@"long: %ld", longValue);
        NSLog(@"long long: %lld", longLongValue);
        NSLog(@"unsigned int: %u", unsignedInt);
        NSLog(@"unsigned long long: %llu", unsignedLongLong);
        
        // ========== 2. 浮点类型 ==========
        NSLog(@"\n--- 浮点类型 ---");
        
        float floatValue = 3.14f;
        double doubleValue = 3.141592653589793;
        long double longDoubleValue = 3.141592653589793238L;
        
        NSLog(@"float: %.2f", floatValue);
        NSLog(@"double: %.15f", doubleValue);
        NSLog(@"long double: %.18Lf", longDoubleValue);
        
        // 科学计数法
        float scientific = 1.5e-10f;
        NSLog(@"科学计数法: %e", scientific);
        
        // ========== 3. 字符类型 ==========
        NSLog(@"\n--- 字符类型 ---");
        
        char charValue = 'A';
        unsigned char unsignedChar = 255;
        
        NSLog(@"char: %c (ASCII: %d)", charValue, charValue);
        NSLog(@"unsigned char: %c (值: %d)", unsignedChar, unsignedChar);
        
        // 字符串（C风格）
        char *cString = "Hello, C String!";
        NSLog(@"C字符串: %s", cString);
        
        // ========== 4. 布尔类型 ==========
        NSLog(@"\n--- 布尔类型 ---");
        
        // Objective-C 使用 BOOL 类型（实际上是 signed char）
        // YES = 1, NO = 0
        BOOL boolTrue = YES;
        BOOL boolFalse = NO;
        BOOL boolFromInt = 1;  // 非零值都是真
        
        NSLog(@"BOOL YES: %d", boolTrue);
        NSLog(@"BOOL NO: %d", boolFalse);
        NSLog(@"BOOL from int: %d", boolFromInt);
        
        // C99 标准布尔类型（需要包含 stdbool.h）
        // _Bool cBool = true;
        
        // ========== 5. 类型转换 ==========
        NSLog(@"\n--- 类型转换 ---");
        
        int intNum = 100;
        float floatNum = 3.14f;
        
        // 隐式转换
        float result1 = intNum + floatNum;  // int 自动转换为 float
        NSLog(@"int + float = %.2f", result1);
        
        // 显式转换（强制类型转换）
        int result2 = (int)floatNum;
        float result3 = (float)intNum;
        NSLog(@"float转int: %d", result2);
        NSLog(@"int转float: %.2f", result3);
        
        // ========== 6. 对象类型（Foundation框架）==========
        NSLog(@"\n--- 对象类型 ---");
        
        // NSString - 不可变字符串
        NSString *string1 = @"Hello, Objective-C!";
        NSString *string2 = [NSString stringWithFormat:@"格式化字符串: %d + %.2f = %.2f", 10, 3.14, 13.14];
        
        NSLog(@"NSString 1: %@", string1);
        NSLog(@"NSString 2: %@", string2);
        
        // NSNumber - 数字对象包装器
        NSNumber *numberInt = @42;  // 字面量语法
        // ⬇️ 等价于 ⬇️
        NSNumber *numberInt2 = [NSNumber numberWithInt:42];
        NSNumber *numberFloat = @3.14f;
        NSNumber *numberBool = @YES;
        NSNumber *numberFromInt = [NSNumber numberWithInt:100];  // 类方法
        
        NSLog(@"NSNumber int: %@", numberInt);
        NSLog(@"NSNumber float: %@", numberFloat);
        NSLog(@"NSNumber bool: %@", numberBool);
        NSLog(@"NSNumber from int: %@", numberFromInt);
        
        // 从 NSNumber 提取值
        int extractedInt = [numberInt intValue];
        float extractedFloat = [numberFloat floatValue];
        BOOL extractedBool = [numberBool boolValue];
        
        NSLog(@"提取的值 - int: %d, float: %.2f, bool: %d", 
              extractedInt, extractedFloat, extractedBool);
        
        // ========== 7. 类型大小（sizeof）==========
        NSLog(@"\n--- 类型大小 ---");
        
        NSLog(@"sizeof(char) = %zu 字节", sizeof(char));
        NSLog(@"sizeof(short) = %zu 字节", sizeof(short));
        NSLog(@"sizeof(int) = %zu 字节", sizeof(int));
        NSLog(@"sizeof(long) = %zu 字节", sizeof(long));
        NSLog(@"sizeof(long long) = %zu 字节", sizeof(long long));
        NSLog(@"sizeof(float) = %zu 字节", sizeof(float));
        NSLog(@"sizeof(double) = %zu 字节", sizeof(double));
        NSLog(@"sizeof(BOOL) = %zu 字节", sizeof(BOOL));
        NSLog(@"sizeof(NSInteger) = %zu 字节", sizeof(NSInteger));
        NSLog(@"sizeof(CGFloat) = %zu 字节", sizeof(CGFloat));
        
        // ========== 8. 平台相关类型 ==========
        NSLog(@"\n--- 平台相关类型 ---");
        
        // NSInteger 和 NSUInteger 会根据平台自动调整
        // 32位系统：long，64位系统：long long
        NSInteger nsInteger = 100;
        NSUInteger nsUInteger = 200;
        
        NSLog(@"NSInteger: %ld", (long)nsInteger);
        NSLog(@"NSUInteger: %lu", (unsigned long)nsUInteger);
        
        // CGFloat 在 64位系统上是 double，32位系统上是 float
        CGFloat cgFloat = 3.14;
        NSLog(@"CGFloat: %.2f", cgFloat);
        
        // ========== 9. 指针类型 ==========
        NSLog(@"\n--- 指针类型 ---");
        
        int value = 100;
        int *pointer = &value;  // 获取地址
        
        NSLog(@"值: %d", value);
        NSLog(@"指针地址: %p", pointer);
        NSLog(@"指针指向的值: %d", *pointer);
        
        // 对象指针（Objective-C 中所有对象都是指针）
        NSString *strPointer = @"对象指针";
        NSLog(@"对象指针: %p", strPointer);
        NSLog(@"对象内容: %@", strPointer);
        
        // ========== 10. 常量 ==========
        NSLog(@"\n--- 常量 ---");
        
        // const 修饰符
        const int CONSTANT_INT = 100;
        const float CONSTANT_FLOAT = 3.14f;
        const NSString *CONSTANT_STRING = @"常量字符串";
        
        NSLog(@"常量 int: %d", CONSTANT_INT);
        NSLog(@"常量 float: %.2f", CONSTANT_FLOAT);
        NSLog(@"常量 string: %@", CONSTANT_STRING);
        
        // #define 宏定义
        #define MAX_VALUE 1000
        #define PI 3.14159
        
        NSLog(@"宏定义 MAX_VALUE: %d", MAX_VALUE);
        NSLog(@"宏定义 PI: %.5f", PI);
        
        NSLog(@"\n========== 示例结束 ==========");
    }
    return 0;
}

