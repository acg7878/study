import Foundation

@propertyWrapper
struct Clamped<T: Comparable> {
    private var value: T
    let min: T
    let max: T
    
    var projectedValue: Bool
    
    init(wrappedValue: T, min: T, max: T) {
        self.min = min
        self.max = max
        let clamped = Self.clamp(wrappedValue, min: min, max: max)
        self.value = clamped
        // 初始化时记录是否被修正
        self.projectedValue = (clamped != wrappedValue)
    }
    
    var wrappedValue: T {
        get { value }
        set {
            let clamped = Self.clamp(newValue, min: min, max: max)
            value = clamped
            // 赋值时更新投影属性状态：如果值变了，说明被修正了
            projectedValue = (clamped != newValue)
        }
    }
    
    private static func clamp(_ value: T, min: T, max: T) -> T {
        if value < min { return min }
        if value > max { return max }
        return value
    }
}

struct Player {
    @Clamped(min: 0, max: 100)
    var score: Int = 50
}

var player = Player()
print("当前分数: \(player.score)") // 输出: 50

// 访问投影属性 (使用 $ 前缀)
// $score 访问的就是 Clamped 结构体里的 projectedValue 属性
print("是否被修正: \(player.$score)") // 输出: false

print("\n=== 尝试设置超范围的值 ===")
player.score = 150
print("当前分数: \(player.score)") // 输出: 100 (被限制了)
print("是否被修正: \(player.$score)") // 输出: true (因为 150 != 100)

print("\n=== 尝试设置正常值 ===")
player.score = 80
print("当前分数: \(player.score)") // 输出: 80
print("是否被修正: \(player.$score)") // 输出: false

