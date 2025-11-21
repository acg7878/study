func printStr(name: String?) {
    guard let test = name else {
        print("name is nil!")
        return
    }
    print("hello,\(test)")
    
}

printStr(name: "man")
printStr(name: nil)

// 与 if let相比
// 更清晰的语义：明确地表达了 “前置条件” 的概念。
// 更安全的保障：编译器强制要求处理不满足条件的情况。

// 更便捷的变量作用域：让绑定的变量可以在后续代码中直接使用。
// 因为if let xx {} 这样创建的变量只能存在于{}