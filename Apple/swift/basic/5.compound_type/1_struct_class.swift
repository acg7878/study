// --- Swift 复合类型学习：结构体与类 ---

import Foundation

// --- 1. 定义结构体 (Struct) ---
// 结构体通常用于封装少量、简单的数据值。
// 它们是值类型 (Value Types)。
print("--------------------------------")
print("1.定义结构体 (Struct)")
struct Person {
    var name: String
    var age: Int

    
    func printInfo() {
        print("Name: \(name), Age: \(age)")
    }
}


// --- 2. 定义类 (Class) ---
// 类支持继承，这使得一个类可以获得另一个类的特性。
// 它们是引用类型 (Reference Types)。
print("--------------------------------")
print("2.定义类 (Class)")
class Animal {
    var name: String
    var size: Double

    init(name: String, size: Double) {
        self.name = name
        self.size = size
    }

    convenience init(name: String) {
        self.init(name: name, size: 1.0)
    }

    convenience init(size: Double) {
        self.init(name: "Unknown", size: size)
    }

    func printInfo() {
        print("Name: \(name), Size: \(size)")
    }
}

class Dog: Animal {
    init(size: Double) {
        super.init(name: "Dog", size: size)
    }
}

// --- 3. 创建和使用实例 ---
print("--------------------------------")
print("3.创建和使用实例")
// 创建结构体实例
// 结构体有一个自动生成的“成员构造器” (memberwise initializer)
var John = Person(name: "John", age: 20)
John.printInfo()


// 访问和修改属性
John.age = 21
John.printInfo()


// 创建类实例
// 必须使用我们自己定义的构造器
var dog = Animal(name: "Dog", size: 1.0)
dog.printInfo()
var Unknown = Animal(size: 1.0)
Unknown.printInfo()

// 访问和修改属性
dog.size = 2.0
dog.printInfo()


// 4.创建子类实例
print("--------------------------------")
print("4.创建子类实例")
var dog2 = Dog(size: 3.0)
dog2.printInfo()

// 总结：
// `struct` 和 `class` 都可以有属性和方法。
// `struct` 有自动的成员构造器，`class` 通常需要自己写。
// `class` 支持继承，`struct` 不支持。
// 它们最核心的区别在于：`struct` 是值类型，`class` 是引用类型。我们将在下一个文件中深入探讨这一点。
