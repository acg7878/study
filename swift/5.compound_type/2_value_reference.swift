// --- Swift 复合类型学习：值类型 vs 引用类型 ---

import Foundation

// --- 准备工作：定义一个 Struct 和一个 Class ---
// 它们有完全相同的属性和方法，以便我们进行公平比较。

// Struct (值类型)
struct PointStruct {
    var x: Int
    var y: Int
    
    mutating func moveRight(by delta: Int) {
        x += delta
    }
}

// Class (引用类型)
class PointClass {
    var x: Int
    var y: Int
    
    init(x: Int, y: Int) {
        self.x = x
        self.y = y
    }
    
    func moveRight(by delta: Int) {
        x += delta
    }
}


// --- 1. 值类型 (Value Type) 的行为 ---
// 当一个值类型的实例（如 struct）被赋值给一个新的变量，
// 或者被传递给一个函数时，它会被“拷贝”。
// 新的变量会得到一个全新的、独立的副本。

print("--- 测试值类型 (Struct) ---")
var structPoint1 = PointStruct(x: 10, y: 20)
var structPoint2 = structPoint1 // 这里发生了拷贝！

print("初始化状态: structPoint1=(\(structPoint1.x), \(structPoint1.y)), structPoint2=(\(structPoint2.x), \(structPoint2.y))")

// 修改 structPoint2
structPoint2.x = 100

print("修改 structPoint2.x 后:")
print("structPoint1 未被修改: (\(structPoint1.x), \(structPoint1.y))")
print("structPoint2 被修改:   (\(structPoint2.x), \(structPoint2.y))")

// 在函数中修改 (注意，函数参数默认是 let 常量，所以不能直接修改)
// 但传递 struct 本身也是一次拷贝
func moveStruct(_ point: PointStruct) {
    var localPoint = point // 创建一个本地可变副本
    localPoint.x += 50
    print("Inside function, localPoint is (\(localPoint.x), \(localPoint.y))")
}
print("\n调用函数 with structPoint1...")
moveStruct(structPoint1)
print("调用函数后, structPoint1 未被修改: (\(structPoint1.x), \(structPoint1.y))")


// --- 2. 引用类型 (Reference Type) 的行为 ---
// 当一个引用类型的实例（如 class）被赋值给一个新的变量时，
// 它并不会被拷贝。相反，新的变量会得到一个指向内存中“同一个”实例的“引用”或“指针”。
// 两个变量指向的是完全相同的东西。

print("\n--- 测试引用类型 (Class) ---")
var classPoint1 = PointClass(x: 10, y: 20)
var classPoint2 = classPoint1 // 这里没有发生拷贝！只是复制了一个引用。

print("初始化状态: classPoint1=(\(classPoint1.x), \(classPoint1.y)), classPoint2=(\(classPoint2.x), \(classPoint2.y))")

// 修改 classPoint2
classPoint2.x = 100

print("修改 classPoint2.x 后:")
print("classPoint1 也被修改: (\(classPoint1.x), \(classPoint1.y))") // <--- 关键区别在这里！
print("classPoint2 被修改:    (\(classPoint2.x), \(classPoint2.y))")

// 在函数中修改
func moveClass(_ point: PointClass) {
    // 这里 point 是指向 classPoint1 实例的另一个引用
    point.x += 50
    print("在函数中, point 被修改: (\(point.x), \(point.y))")
}
print("\n调用函数 with classPoint1...")
moveClass(classPoint1)
print("调用函数后, classPoint1 也被修改: (\(classPoint1.x), \(classPoint1.y))")


// --- 3. 恒等运算符 (Identity Operators) ---
// 对于引用类型，你可以检查两个常量或变量是否指向完全相同的实例。
// `===` (恒等于) 和 `!==` (不恒等于)

if classPoint1 === classPoint2 {
    print("\nclassPoint1 和 classPoint2 指向同一个实例.")
}

let classPoint3 = PointClass(x: 150, y: 20)
if classPoint1 !== classPoint3 {
    print("classPoint1 和 classPoint3 指向不同的实例.")
}

// 总结:
// - 把 `struct` 想象成一张照片的复印件，修改复印件不会影响原件。
// - 把 `class` 想象成一张照片的网络链接，通过任何一个链接去修改照片，所有人都会看到修改后的版本。
// - 在 Swift 中，优先使用 `struct`，除非你需要引用类型的特定行为（比如继承或恒等性检查）。
