// `MainActor` 是 Swift 并发模型中的一个全局 Actor，它的核心功能只有一个：
// 强制被它标记的代码块，总是在应用程序的主线程上执行


// 在几乎所有的UI框架 (SwiftUI, UIKit, AppKit) 中，都有一条铁律：
// 所有对用户界面的创建、修改和访问都必须在主线程 (Main Thread) 上进行。
// 在后台线程操作UI会导致程序崩溃或界面异常。


@MainActor
class MainActorExample {
    // UI中才能生效
    // 这里不演示代码
}
