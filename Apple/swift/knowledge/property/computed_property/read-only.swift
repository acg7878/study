// 如果一个计算属性只有 getter 没有 setter，那么它就是一个只读计算属性

struct Person {
    var firstName: String
    var lastName: String

    // 这三个写法一样效果

    // 隐式返回：如果 getter 的函数体只有一行表达式，Swift 允许省略 return 关键字
    var fullName: String {
        firstName + lastName
    }

    // 最标准
    // var fullName : String {
    //     get {
    //         return firstName + lastName
    //     }
    // }

    // var fullName : String {
    //     return "\(firstName)\(lastName)"
    // }
}

let xiaoming = Person(firstName: "xiao", lastName: "ming")
print(xiaoming.fullName)