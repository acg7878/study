import Foundation

// 可选类型
var name : String? = "xiaoming"

// 安全解包
if let name = name {
    print(name);
} else {
    print("if:name为空！")
}
guard let name = name else{
    print("guard:name为空！")
    exit(0)
}

// 强制解包
// 危险，如果为nil就会崩溃
var age : Int? = 123
let myAge = age!
print(myAge)

// 空合运算符
var age2 : Int? = nil
var testAge = age2 ?? -1
print(testAge)

