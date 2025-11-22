
#import <Foundation/Foundation.h>
#include <stdio.h>

int main() {
    int (^add)(int,int) = ^int(int a,int b) {
        return  a+b;
    };
    int result = add(1,2);
    printf("1+2=%d\n",result);

    // typedef alias
    // typedef returnType (^blockName)(paramters)
    typedef int (^multiBlock)(int,int);
    multiBlock multi = ^(int a,int b) {
        return a*b;
    };
    printf("5*2=%d",multi(5,2));
}