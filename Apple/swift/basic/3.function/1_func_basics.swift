// --- Swift 函数学习：定义与调用 ---

import Foundation

// --- 1. 定义和调用函数 ---
print("--------------------------------")
print("1.定义和调用函数")
func hello(){
    print("hello!")
}
hello()



// --- 2. 函数参数 (Parameters) ---
print("--------------------------------")
print("2.函数参数")
func hello(_ name:String) {
    print("hello!\(name)")
}
hello("yjk")

// --- 3. 函数返回值 (Return Values) ---
print("--------------------------------")
print("3.函数返回值")
func hello_echo(_ name:String) -> String {
    print("hello!\(name)")
    return "hello too!"
}
print(hello_echo("crh"))




// --- 4. 参数标签和参数名 ---
print("--------------------------------")
print("4.参数标签和参数名")
// Swift 的函数参数有一个非常重要的特性：它区分为函数内部使用的“参数名”和函数外部调用时使用的“参数标签”。
// 默认情况下，参数名既是内部名也是外部标签。
// func someFunction(parameterName: Int)
// 你可以为参数指定一个不同的外部标签。
func greet(person: String, from hometown: String) {
    // 在函数内部，你使用 `person` 和 `hometown`
    print("Hello \(person)! Glad you could join us from \(hometown).")
}

// 在函数调用时，你使用外部标签 `from`。这让代码读起来像一个句子。
greet(person: "Bill", from: "Cupertino")
// 如果你不希望参数有外部标签，可以使用下划线 `_`。
func addTwoNumbers(_ a: Int, _ b: Int) -> Int {
    return a + b
}
let sum = addTwoNumbers(5, 3) // 调用时不需要写标签
print("Sum is \(sum)")


// --- 5. 默认参数值 ---
print("--------------------------------")
print("5.默认参数值")
// 你可以为函数的任何参数提供一个默认值。
// 如果提供了默认值，那么在调用函数时就可以省略这个参数。

func someFunction(parameterWithoutDefault: Int, parameterWithDefault: Int = 12) {
    print("param1: \(parameterWithoutDefault), param2: \(parameterWithDefault)")
}

someFunction(parameterWithoutDefault: 3, parameterWithDefault: 6) // 提供了第二个参数，使用 6
someFunction(parameterWithoutDefault: 4) // 没有提供第二个参数，使用默认值 12


// --- 6. 可变参数 (Variadic Parameters) ---
print("--------------------------------")
print("6.可变参数")
// 可变参数可以接受零个或多个指定类型的值。
// 在参数类型名后加上 `...` 来表示。

func arithmeticMean(_ numbers: Double...) -> Double {
    var total: Double = 0
    // 在函数内部，可变参数被当作一个数组来使用。
    for number in numbers {
        total += number
    }
    return total / Double(numbers.count)
}

print(arithmeticMean(1, 2, 3, 4, 5))
print(arithmeticMean(3, 8.25, 18.75))


// --- 7. 输入输出参数 (In-Out Parameters) ---
print("--------------------------------")
print("7.输入输出参数")
// 通常，函数的参数是常量，你不能在函数内部修改它们的值。
// 如果你想让一个函数能够修改传入的变量的值，就需要使用 `inout` 参数。

func swapTwoInts(_ a: inout Int, _ b: inout Int) {
    let temporaryA = a
    a = b
    b = temporaryA
}

var someInt = 3
var anotherInt = 107
print("Before swap: \(someInt), \(anotherInt)")

// 调用时，需要在变量名前加上 `&` 符号，表示这个值可能会被函数修改。
swapTwoInts(&someInt, &anotherInt)

print("After swap: \(someInt), \(anotherInt)")
