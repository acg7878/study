// 属性包装器 是一个遵循 PropertyWrapper 协议的结构体、类或枚举。
// 它的核心作用是 “包装” 一个属性，将该属性的 存储 和 访问逻辑 委托给包装器本身。

import Foundation

@propertyWrapper
struct Clamped<T: Comparable> {
    private var value: T
    let min: T
    let max: T

    init(wrappedValue: T, min: T, max: T) {
        self.min = min
        self.max = max
        self.value = Self.clamp(wrappedValue, min: min, max: max)
    }

    var wrappedValue: T {
        get { value }
        set { value = Self.clamp(newValue, min: min, max: max) }
    }

    private static func clamp(_ value: T, min: T, max: T) -> T {
        if value < min { return min }  // 如果值小于最小值，返回最小值
        if value > max { return max }  // 如果值大于最大值，返回最大值
        return value  // 否则返回值
    }
}
@propertyWrapper
struct Lazy<T> {
    private var value: T?
    private let initializer: () -> T

    init(wrappedValue initializer: @escaping @autoclosure () -> T) {
        self.initializer = initializer
    }

    var wrappedValue: T {
        mutating get {
            if value == nil {
                value = initializer()
            }
            return value!
        }
        set {
            value = newValue
        }
    }
}
@propertyWrapper
struct Uppercased {
    private var value: String

    init(wrappedValue: String) {
        self.value = wrappedValue.uppercased()
    }

    var wrappedValue: String {
        get { value }
        set { value = newValue.uppercased() }
    }
}
@propertyWrapper
struct Logged<T> {
    private var value: T
    let name: String

    init(wrappedValue: T, name: String = "") {
        self.value = wrappedValue
        self.name = name
    }

    var wrappedValue: T {
        get {
            print("📖 读取 \(name.isEmpty ? "属性" : name): \(value)")
            return value
        }
        set {
            print("✏️  写入 \(name.isEmpty ? "属性" : name): \(newValue)")
            value = newValue
        }
    }
}
struct Player {
    @Clamped(min: 0, max: 100)
    var score: Int = 50 // 访问score实际上是访问Clamped包装器的wrappedValue

    @Uppercased
    var name: String = "player"

    @Logged(name: "等级")
    var level: Int = 1

    @Lazy
    var expensiveData: String = {
        print("正在初始化昂贵的数据...")
        return "这是延迟加载的数据"
    }()
}
var player = Player()
print("\n=== 测试 Clamped ===")
player.score = 150
print("分数: \(player.score)")
player.score = -10
print("分数: \(player.score)")
print("\n=== 测试 Uppercased ===")
player.name = "john doe"
print("姓名: \(player.name)")
print("\n=== 测试 Logged ===")
player.level = 5
let currentLevel = player.level
print("\n=== 测试 Lazy ===")
print("首次访问:")
let data1 = player.expensiveData
print("再次访问:")
let data2 = player.expensiveData
print("数据: \(data1)")
