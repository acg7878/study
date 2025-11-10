// --- 5. Guard 语句 ---
// Guard 语句用于提前退出，是 Swift 中非常常用的语法。
// 它能让代码的可读性变得更好，避免深层次的 if-let 嵌套。

func greet(person: [String: String]) {
    // 使用 guard let 来安全地解包可选类型
    // 如果 name 不存在，就执行 else block 然后退出函数
    guard let name = person["name"] else {
        print("Error: 'name' key not found.")
        return
    }

    // 执行到这里时，`name` 已经是一个解包后的、可用的 String
    print("Hello \(name)!")

    // 再解包 location
    guard let location = person["location"] else {
        print("I hope the weather is nice near you.")
        return
    }

    print("I hope the weather is nice in \(location).")
}

greet(person: ["name": "John"])
// 输出:
// Hello John!
// I hope the weather is nice near you.

greet(person: ["name": "Jane", "location": "Cupertino"])
// 输出:
// Hello Jane!
// I hope the weather is nice in Cupertino.

greet(person: [:])
// 输出:
// Error: 'name' key not found.
