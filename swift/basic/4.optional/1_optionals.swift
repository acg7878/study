// --- Swift 可选类型学习 ---

import Foundation

// --- 1. 什么是可选类型 (Optionals) ---

// `possibleNumber` 是一个可选字符串。它可能包含一个 String，也可能什么都没有（nil）。
// 类型 `String?` 和 `String` 是完全不同的两种类型。
var possibleNumber: String? = "123"
possibleNumber = nil // 我们可以给它赋值为 nil

// `definiteNumber` 是一个普通字符串，它必须有一个值，不能被赋值为 nil。
var definiteNumber: String = "456"
// definiteNumber = nil // 这行代码会直接导致编译错误


// --- 2. 强制解包 (Forced Unwrapping) ---
// 如果你非常确定一个可选类型一定有值，你可以在它后面加上 `!` 来强制解包。
// 这就像在说：“我知道这里有值，直接把它拿出来用。”

var definitelyHasAValue: String? = "Hello"
print(definitelyHasAValue!) // 输出 "Hello"

// **警告**：如果此时可选值为 nil，强制解包会导致程序立即崩溃！
// var mightBeNil: String? = nil
// print(mightBeNil!) // 这行代码会使程序崩溃

// 结论：除非你 100% 确定，否则应极力避免使用强制解包。


// --- 3. 可选绑定 (Optional Binding) ---
// 这是处理可选值的最安全、最常见的方式。
// 它会尝试解包可选值，如果成功，就把解包后的值赋给一个新的常量或变量。

var maybeANumberString: String? = "abc"

// 使用 `if let`
if let numberString = maybeANumberString {
    // 这个代码块只会在 `maybeANumberString` 不为 nil 时执行。
    // 在这个代码块内部，`numberString` 是一个普通的、解包后的 `String`，而不是 `String?`。
    print("It's a string with value: '\(numberString)'")
} else {
    // 如果 `maybeANumberString` 是 nil，就会执行 else 块。
    print("It's nil.")
}

// `if let` 也可以同时解包多个可选值
let optionalA: Int? = 5
let optionalB: Int? = 10
if let a = optionalA, let b = optionalB {
    // 只有当 a 和 b 都有值时，这里才会执行
    print("Sum is \(a + b)")
}


// --- 4. Guard Let ---
// `guard let` 和 `if let` 类似，但它通常用于在函数或循环的开头“提前退出”。
// 这让代码的可读性变得更好，避免了深度的 `if` 嵌套。

func process(someOptional: String?) {
    guard let unwrappedValue = someOptional else {
        // 如果 someOptional 是 nil，就执行这个代码块并立即退出函数。
        print("Received nil, cannot process.")
        return
    }
    
    // 在 guard 语句之后的所有代码中，`unwrappedValue` 都是可用的、解包后的值。
    print("Processing value: \(unwrappedValue)")
}

process(someOptional: "Test Data") // 输出 "Processing value: Test Data"
process(someOptional: nil)         // 输出 "Received nil, cannot process."


// --- 5. 空合运算符 (Nil-Coalescing Operator) ---
// `a ?? b` 的意思是：“如果 `a` 不是 `nil`，就使用 `a` 解包后的值；如果 `a` 是 `nil`，就使用默认值 `b`。”
// `b` 的类型必须和 `a` 所包裹的类型相匹配。

let defaultColorName = "red"
var userDefinedColorName: String? // 当前是 nil

var colorNameToUse = userDefinedColorName ?? defaultColorName
print("Color to use: \(colorNameToUse)") // 输出 "Color to use: red"

userDefinedColorName = "blue"
colorNameToUse = userDefinedColorName ?? defaultColorName
print("Color to use: \(colorNameToUse)") // 输出 "Color to use: blue"


// --- 6. 可选链 (Optional Chaining) ---
// 当你需要访问一个可选值的属性或方法时，可以使用可选链。
// 如果可选值是 `nil`，整个调用链会优雅地失败，并返回 `nil`，而不会崩溃。

class Person {
    var residence: Residence?
}

class Residence {
    var numberOfRooms = 1
}

let john = Person()
// john.residence 是 nil，所以 `john.residence?.numberOfRooms` 整个表达式的结果也是 nil
if let roomCount = john.residence?.numberOfRooms {
    print("John's residence has \(roomCount) room(s).")
} else {
    print("Unable to retrieve the number of rooms.") // 这句会被执行
}

john.residence = Residence()
if let roomCount = john.residence?.numberOfRooms {
    print("John's residence has \(roomCount) room(s).") // 这句会被执行
}
