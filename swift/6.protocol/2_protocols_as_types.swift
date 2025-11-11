// --- Swift 协议学习：协议作为类型 ---

import Foundation

// --- 准备工作：定义一个协议和几个遵守它的类型 ---
protocol Taggable {
    var tag: String { get }
    func tagDescription() -> String
}

struct Book: Taggable {
    var title: String
    var author: String
    
    var tag: String {
        return "Book-\(title.prefix(4))"
    }
    
    func tagDescription() -> String {
        return "This is a book named '\(title)' by \(author)."
    }
}

struct Car: Taggable {
    var make: String
    var model: String
    
    var tag: String {
        return "Car-\(make)-\(model)"
    }
    
    func tagDescription() -> String {
        return "This is a \(make) \(model)."
    }
}

class Monitor: Taggable {
    var brand: String
    var resolution: String

    init(brand: String, resolution: String) {
        self.brand = brand
        self.resolution = resolution
    }

    var tag: String {
        return "Monitor-\(brand)"
    }

    func tagDescription() -> String {
        return "A \(resolution) monitor from \(brand)."
    }
}


// --- 1. 将协议作为参数类型 ---
// 这个函数不关心传入的是 Book, Car, 还是 Monitor。
// 它只关心传入的东西是否遵守 `Taggable` 协议。
// 这样就实现了代码的解耦。
func printTag(for item: Taggable) {
    print("Item Tag: \(item.tag)")
    print("Description: \(item.tagDescription())")
    print("---")
}

let aGreatBook = Book(title: "The Lord of the Rings", author: "J.R.R. Tolkien")
let myCar = Car(make: "Tesla", model: "Model 3")
let myMonitor = Monitor(brand: "Apple", resolution: "5K")

printTag(for: aGreatBook)
printTag(for: myCar)
printTag(for: myMonitor)


// --- 2. 将协议用在集合中 ---
// 我们可以创建一个数组，它的元素类型是 `Taggable` 协议。
// 这意味着这个数组可以存储任何遵守 `Taggable` 协议的类型的实例，
// 即使这些实例的具体类型各不相同（Book, Car, Monitor）。
// 这对于类来说，有点像使用一个共同的基类，但协议连值类型（struct）也能支持！

let taggableItems: [Taggable] = [aGreatBook, myCar, myMonitor]

print("\n--- Looping through mixed-type array ---")
for item in taggableItems {
    // 我们可以安全地调用 `tag` 属性，因为我们知道数组中的每个元素都遵守 Taggable 协议
    print("Processing tag: \(item.tag)")
    
    // 如果我们想知道元素的具体类型，可以使用类型转换操作符 `is` 和 `as?`
    if item is Book {
        print("This item is a Book.")
    }
    
    if let car = item as? Car {
        print("Found a Car! Make: \(car.make)")
    }
    print("---")
}

// 总结：
// 将协议作为类型使用，是实现“多态”和编写通用、灵活代码的关键。
// 它允许你编写不依赖于具体实现细节的函数和数据结构。
