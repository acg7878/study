// --- Swift 闭包学习：在标准 API 中的应用 ---

import Foundation

let numbers = [1, 5, 2, 8, 3, 9, 4, 6, 7]
print("Original numbers: \(numbers)")


// --- 1. `sorted(by:)` ---
// `sorted` 方法可以接受一个闭包作为参数，这个闭包定义了如何比较两个元素。
// 这个闭包需要接受两个元素，如果第一个元素应该排在第二个元素前面，就返回 `true`。

// 使用尾随闭包语法进行降序排序
let descendingNumbers = numbers.sorted { (a, b) -> Bool in
    return a > b
}
print("Descending numbers: \(descendingNumbers)")

// 使用更简洁的语法
let descendingNumbersSimplified = numbers.sorted { $0 > $1 }
print("Descending numbers (simplified): \(descendingNumbersSimplified)")


// --- 2. `map` ---
// `map` 方法可以用一个闭包来转换数组中的每一个元素，并返回一个新的数组。

// 将每个数字都转换成它的字符串形式
let numberStrings = numbers.map { (number) -> String in
    return "Number \(number)"
}
print("Number strings: \(numberStrings)")

// 简化版
let simplifiedNumberStrings = numbers.map { "Number \($0)" }
print("Number strings (simplified): \(simplifiedNumberStrings)")


// --- 3. `filter` ---
// `filter` 方法可以用一个闭包来测试数组中的每一个元素，并返回一个只包含通过测试的元素的新数组。
// 闭包需要返回一个布尔值。

// 只保留偶数
let evenNumbers = numbers.filter { (number) -> Bool in
    return number % 2 == 0
}
print("Even numbers: \(evenNumbers)")

// 简化版
let simplifiedEvenNumbers = numbers.filter { $0 % 2 == 0 }
print("Even numbers (simplified): \(simplifiedEvenNumbers)")


// --- 4. `reduce` ---
// `reduce` 方法可以将数组中的所有元素组合成一个单一的值。
// 它接受一个初始值和一个闭包。闭包接受两个参数：一个是到目前为止的累计结果，另一个是数组中的下一个元素。

// 计算所有数字的总和
// 0 是初始值，`result` 是累计结果，`number` 是下一个元素
let sumOfAllNumbers = numbers.reduce(0) { (result, number) -> Int in
    return result + number
}
print("Sum of all numbers: \(sumOfAllNumbers)")

// 简化版
let simplifiedSum = numbers.reduce(0) { $0 + $1 }
// 甚至可以更简化
let simplestSum = numbers.reduce(0, +)
print("Sum of all numbers (simplified): \(simplestSum)")


// --- 5. 链式调用 (Chaining) ---
// 这些方法最强大的地方在于它们可以被链接在一起，形成一个清晰、声明式的数据处理流程。

// 需求：从数字数组中，筛选出奇数，将它们平方，然后计算它们的总和。
let result = numbers
    .filter { $0 % 2 != 0 }          // [1, 5, 3, 9, 7]
    .map { $0 * $0 }                 // [1, 25, 9, 81, 49]
    .reduce(0, +)                    // 1 + 25 + 9 + 81 + 49 = 165

print("Sum of squares of odd numbers: \(result)")
