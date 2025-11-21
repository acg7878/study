import Foundation

struct Square {
    // 存储属性：确实把值存在内存里
    var sideLength: Double
    
    // 1. 读写计算属性 (Read-Write)
    // 不存储值，每次访问都会重新计算
    var area: Double {
        get {
            return sideLength * sideLength
        }
        set {
            // 'newValue' 是默认参数名，代表赋给 area 的新值
            sideLength = sqrt(newValue)
        }
    }
    
    // 2. 只读计算属性 (Read-Only)
    // 只有 getter，必须用 var 定义（因为值可能改变）
    // 简写形式：省略 get {}
    var perimeter: Double {
        return sideLength * 4
    }
}

// 测试
var sq = Square(sideLength: 5)
print("初始边长: \(sq.sideLength)") // 5.0
print("计算出的面积: \(sq.area)")     // 25.0

// 修改计算属性
sq.area = 36
print("修改面积为 36 后，边长变为: \(sq.sideLength)") // 6.0

sq.sideLength = 7
print("直接修改边长为 7 后，面积变为: \(sq.area)") // 49.0
print("计算出的周长: \(sq.perimeter)") // 28.0

