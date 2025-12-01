import Foundation
// Actor：数据隔离+串行执行


// Actor 内部的所有属性（状态）仅能被 Actor 自身的方法访问，外部无法直接读写
// 必须通过 Actor 暴露的方法间接操作
actor FavoritesManager {
    private var favorites: Set<String> = []
    
    init(initialFavorites: [String] = []) {
        self.favorites = Set(initialFavorites)
    }

    // 这些方法在 Actor 内部是同步执行的，但在外部必须异步调用
    
    /// 将一个 ID 添加到收藏列表
    func add(favorite id: String) {
        print("✅ [Actor] 正在尝试添加: \(id)")
        favorites.insert(id)
    }
    
    func remove(favorite id: String) {
        print("❌ [Actor] 正在尝试移除: \(id)")
        favorites.remove(id)
    }
    
    /// 检查某个 ID 是否在收藏列表中
    /// 这个方法有返回值，外部调用时也需要 await
    func isFavorite(id: String) -> Bool {
        let result = favorites.contains(id)
        print("❓ [Actor] 检查 \(id) 是否收藏: \(result)")
        return result
    }
    
    /// 获取当前所有收藏的副本
    /// 返回值是 [String]，而不是 Set，方便外部使用
    func getAllFavorites() -> [String] {
        print("📋 [Actor] 获取所有收藏")
        return Array(favorites)
    }
}


let manager = FavoritesManager(initialFavorites: ["item001", "item002"])

// 模拟并发地进行操作
func simulateConcurrentAccess() {
    
    print("--- 开始模拟并发访问 ---")
    // 添加一个新的收藏，然后检查另一个
    Task {
        print("  [Task 1] 启动")
        await manager.add(favorite: "item101")
        _ = await manager.isFavorite(id: "item001")
        print("  [Task 1] 完成")
    }
    
    // 移除一个已有的收藏，然后添加一个新的
    Task {
        print("  [Task 2] 启动")
        await manager.remove(favorite: "item002")
        await manager.add(favorite: "item202")
        print("  [Task 2] 完成")
    }
    
    // 连续检查两个商品的状态
    Task {
        print("  [Task 3] 启动")
        _ = await manager.isFavorite(id: "item101") // 可能会检查到 Task 1 的结果
        _ = await manager.isFavorite(id: "item999") // 一个不存在的商品
        print("  [Task 3] 完成")
    }
}

// 主执行函数
func runExample() async {
    simulateConcurrentAccess()
    try? await Task.sleep(nanoseconds: 1_000_000_000) // 1秒
    
    print("\n--- 并发访问结束后，查看最终结果 ---")
    let finalFavorites = await manager.getAllFavorites()
    print("最终的收藏列表: \(finalFavorites.sorted())")
}


await runExample()