// 延迟存储属性是一种特殊的存储属性，它的初始值会在第一次被访问时才计算和分配内存
class DataManager {
    var isInitData: Bool = false

    lazy var largeData: [Int] = {
        isInitData = true
        return Array(1...100000)
    }()
    // () 为立即执行闭包，但是由于lazy修饰被延迟到属性首次访问
}

let manager = DataManager()

// if let只能用于可选类型！
if !manager.isInitData {
    print("未加载")
}
let dataCount = manager.largeData.count
if manager.isInitData {
    print("已加载")
}