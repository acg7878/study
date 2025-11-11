// --- Swift 协议学习：协议扩展 ---

import Foundation

// --- 准备工作：定义一个协议和几个遵守它的类型 ---

protocol Describable {
    var description: String { get }
    func detailedDescription() -> String
}

struct Product: Describable {
    var name: String
    var price: Double
    
    // `Product` 提供了自己的 `description` 实现
    var description: String {
        return "'\(name)' - $\(price)"
    }
    
    // 它也提供了自己的 `detailedDescription` 实现
    func detailedDescription() -> String {
        return "This is a product named \(name), which costs \(price)."
    }
}

struct Service: Describable {
    var name: String
    var hourlyRate: Double
    
    // `Service` 也提供了自己的 `description` 实现
    var description: String {
        return "'\(name)' - $\(hourlyRate)/hour"
    }
    
    // 注意：`Service` 没有提供 `detailedDescription` 的实现！
}


// --- 1. 使用协议扩展提供默认实现 ---

extension Describable {
    // 我们为 `detailedDescription` 方法提供了一个默认实现
    func detailedDescription() -> String {
        // 这个默认实现会使用协议自身要求的 `description` 属性
        return "Item description: \(description)"
    }
}


// --- 2. 观察默认实现的效果 ---

let macbook = Product(name: "MacBook Pro", price: 1999.0)
let consulting = Service(name: "Swift Consulting", hourlyRate: 150.0)

// `macbook` 调用它自己的 `detailedDescription` 实现
print(macbook.detailedDescription())
// 输出: "This is a product named MacBook Pro, which costs $1999.0."


// `consulting` 自身没有实现 `detailedDescription`，
// 因此它会自动获得并使用我们通过协议扩展提供的“默认版本”。
print(consulting.detailedDescription())
// 输出: "Item description: 'Swift Consulting' - $150.0/hour"


// --- 3. 为 Swift 已有类型添加协议遵守 ---
// 协议扩展的另一个强大之处在于，你可以让你无法直接修改的、
// Swift 自带的类型（如 Array, Int, String）也遵守你的协议。

// 假设我们希望一个 `Array` 也能被描述
extension Array: Describable where Element: Describable {
    // 我们为 Array 添加 `description` 的实现
    var description: String {
        if self.isEmpty {
            return "An empty array."
        } else {
            return "An array with \(self.count) items."
        }
    }
    // `detailedDescription` 会自动使用我们上面定义的默认实现
}

let productArray = [macbook, Product(name: "Magic Mouse", price: 99.0)]
let emptyArray: [Service] = []

print(productArray.description) // 输出: "An array with 2 items."
print(productArray.detailedDescription()) // 输出: "Item description: An array with 2 items."

print(emptyArray.description) // 输出: "An empty array."


// 总结：
// 协议扩展是一种极其强大的代码复用机制。
// 它允许你定义一套默认行为，然后让任何类型通过遵守协议来“混入”(mixin) 这套行为。
// 这是面向协议编程思想的核心，鼓励使用组合（通过协议）而非继承来构建功能。
