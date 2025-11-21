import Foundation
#if canImport(FoundationNetworking)
import FoundationNetworking
#endif

func pingBaidu() async throws -> String {
    print("正在网络请求...")
    // 模拟网络延迟 2 秒
    try await Task.sleep(nanoseconds:  1_000_000_000)
    print("请求完成。")
    return "<html><body><h1>这是一个模拟的百度首页</h1></body></html>"
}

Task {
    do {
        print("开始请求...")
        let html = try await pingBaidu()
        print("请求成功，内容预览: \(html.prefix(100))...")
    } catch {
        print("请求失败: \(error)")
    }
}

// 暂停一下，不然还没执行就退出了
RunLoop.main.run(until: Date(timeIntervalSinceNow: 3))