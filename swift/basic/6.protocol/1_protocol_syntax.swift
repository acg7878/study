// --- Swift 协议学习：协议语法 ---

import Foundation

// --- 1. 定义协议 ---
// 协议定义了一个蓝图，规定了属性和方法的要求。

protocol FullyNamed {
    // get: 可读，set: 可写
    var fullName: String { get set }
    func introduce()
}


// --- 2. 遵守协议 ---
// 不同的类型（struct, class, enum）都可以遵守同一个协议。
// 在类型名称后面加上冒号和协议名称。

// `Person` 结构体遵守 `FullyNamed` 协议
struct Person: FullyNamed {
    // 提供了协议要求的 `fullName` 属性
    var fullName: String
    
    // 自动提供了get、set
    // 比如person.fullName = "John Appleseed", 会自动调用set方法
    // 比如print(person.fullName), 会自动调用get方法


    // 提供协议要求的 `introduce` 方法
    func introduce() {
        print("Hello, my name is \(fullName).")
    }
}

// `User` 类也遵守 `FullyNamed` 协议
class User: FullyNamed {
    var username: String
    var email: String
    
    // 同样提供了协议要求的 `fullName` 属性
    var fullName: String {
        get {
            return username // 这是一个计算属性
        }
        set {
            self.username = newValue
        }
    }
    
    init(username: String, email: String) {
        self.username = username
        self.email = email
    }
    
    // 同样提供了协议要求的 `introduce` 方法
    func introduce() {
        print("Hi, I'm user '\(username)'.")
    }
}


// --- 3. 使用遵守协议的类型 ---
let john = Person(fullName: "John Appleseed")
john.introduce() // 输出 "Hello, my name is John Appleseed."

var jane = User(username: "JaneDoe", email: "jane@example.com")
jane.introduce() // 输出 "Hi, I'm user 'JaneDoe'."
print("Jane's full name is: \(jane.fullName)")
jane.fullName = "Jane Smith"
print("Jane's new username is: \(jane.username)")


// --- 4. 协议继承 ---
// 一个协议可以继承一个或多个其他协议。

protocol Identifiable {
    var id: String { get } // 只需要可读
}

// `Loggable` 协议继承了 `Identifiable` 和 `FullyNamed`
protocol Loggable: Identifiable, FullyNamed {
    var logMessage: String { get }
}

// `SystemProcess` 遵守 `Loggable` 协议
struct SystemProcess: Loggable {
    // 必须实现 Loggable 自身的要求
    var logMessage: String {
        return "Process \(id): \(fullName)"
    }
    
    // 还必须实现它所继承的 Identifiable 的要求
    var id: String
    
    // 还必须实现它所继承的 FullyNamed 的要求
    var fullName: String
    
    func introduce() {
        print("System Process: \(fullName)")
    }
}

let process = SystemProcess(id: "PID123", fullName: "com.apple.kernel")
print(process.logMessage) // 输出 "Process PID123: com.apple.kernel"

// 总结：
// 协议定义了“做什么”，而不是“怎么做”。
// 任何类型都可以通过实现协议的要求来“遵守”它。
// 这使得我们可以为完全不相关的类型定义一套共同的行为标准。
