// --- 2. Switch 语句 ---
// Swift 的 switch 语句非常强大，并且必须是穷尽的（exhaustive）。
// 这意味着所有可能的情况都必须被考虑到。

let someCharacter: Character = "z"
switch someCharacter {
case "a", "A":
    print("The first letter of the alphabet")
case "z", "Z":
    print("The last letter of the alphabet")
default: // `default` case 保证了穷尽性
    print("Some other character")
}

// Switch 可以匹配区间
let approximateCount = 62
switch approximateCount {
case 0:
    print("none")
case 1..<5:
    print("a few")
case 5..<12:
    print("several")
case 12..<100:
    print("dozens of")
case 100..<1000:
    print("hundreds of")
default:
    print("many")
}

// Switch 可以匹配元组 (Tuples)
let somePoint = (1, 1)
switch somePoint {
case (0, 0):
    print("\(somePoint) is at the origin")
case (_, 0): // `_` 是通配符，可以匹配任何值
    print("\(somePoint) is on the x-axis")
case (0, _):
    print("\(somePoint) is on the y-axis")
case (-2...2, -2...2):
    print("\(somePoint) is inside the box")
default:
    print("\(somePoint) is outside of the box")
}

// 值绑定 (Value Binding) 和 `where` 子句
let anotherPoint = (2, 0)
switch anotherPoint {
case (let x, 0): // 将匹配到的元组第一个元素的值绑定到常量 x
    print("on the x-axis with an x value of \(x)")
case (0, let y): // 将匹配到的元组第二个元素的值绑定到常量 y
    print("on the y-axis with a y value of \(y)")
case let (x, y) where x == y: // 使用 where 子句添加额外条件
    print("on the line x == y")
case let (x, y):
    print("somewhere else at (\(x), \(y))")
}
