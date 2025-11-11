// --- Swift 闭包学习：闭包语法 ---

import Foundation
func operateOnNumbers(_ a: Int, _ b: Int, operation: (Int, Int) -> Int) -> Int {
    let result = operation(a, b)
    print("Performing operation on \(a) and \(b), result is \(result)")
    return result
}

func add(_ a: Int, _ b: Int) -> Int {
    return a + b
}

// 我们可以把这个函数作为参数传递
print(operateOnNumbers(10, 5, operation: add))


// --- 1. 闭包的完整语法 ---
print(operateOnNumbers(10, 5, operation: { (a: Int, b: Int) -> Int in
    // `in` 关键字后面是闭包的执行体
    return a + b
}))


// --- 2. 语法简化：利用类型推断 ---
// 因为 `operateOnNumbers` 函数已经声明了 `operation` 参数的类型是 `(Int, Int) -> Int`，
// 所以 Swift 可以推断出闭包参数 `a` 和 `b` 的类型是 `Int`，返回类型也是 `Int`。
// 我们可以省略类型声明。
print(operateOnNumbers(10, 5, operation: { (a, b) in
    return a + b
}))


// --- 3. 语法简化：单表达式闭包的隐式返回 ---
// 如果闭包的执行体只包含一个单行表达式（如此处的 `a + b`），
// 那么 Swift 会自动将这个表达式的结果作为返回值。
// 我们可以省略 `return` 关键字。

print(operateOnNumbers(10, 5, operation: { (a, b) in
    a + b
}))


// --- 4. 语法简化：参数名称缩写 ---
// Swift 会自动为闭包提供参数的缩写名称，`$0` 代表第一个参数，`$1` 代表第二个，以此类推。
// 如果你使用了这些缩写，你就可以省略参数列表和 `in` 关键字。
print(operateOnNumbers(10, 5, operation: {
    $0 + $1
}))


// --- 5. 语法简化：运算符作为函数 ---
// 对于像 `+` 这样的运算符，Swift 实际上知道它是一个接受两个参数并返回一个值的“函数”。
// 如果一个闭包只是简单地调用了一个这样的运算符，你可以直接把这个运算符传递过去。
// 这是最简洁的形态。
print(operateOnNumbers(10, 5, operation: +))


// --- 6. 尾随闭包 (Trailing Closure) ---
// 这是一个非常非常常见的 Swift 特性
// 如果一个函数的最后一个参数是闭包，那么你可以将这个闭包写在函数调用的括号 `)` 之后。

// 这是未使用尾随闭包的写法
print(operateOnNumbers(10, 5, operation: { $0 * $1 }))
// 这是使用尾随闭包的写法
print(operateOnNumbers(10, 5) { $0 * $1 })

// 如果函数除了闭包之外没有其他参数，你甚至可以完全省略括号 `()`
let names = ["Chris", "Alex", "Ewa", "Barry", "Daniella"]
let sortedNames = names.sorted { $0 > $1 } // sorted 函数只接受一个闭包参数
print(sortedNames)

// 总结：
// 闭包是功能强大的“内联函数”。
// 它们的语法非常灵活，可以根据上下文进行大幅简化。
// 尾随闭包是 Swift 代码风格的重要组成部分，能让代码更具可读性。
