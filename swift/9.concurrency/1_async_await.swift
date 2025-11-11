// --- Swift 并发学习：Async/Await ---

import Foundation

// 在 Windows 上，为了让并发功能正常工作，我们需要在文件的顶层添加 @main 注解
// 和一个异步的主函数。这是平台特定的一个要求。
@main
struct Main {
    static func main() async {
        print("--- 学习 Swift 现代并发编程 ---")
        
        // --- 1. 定义和调用异步函数 ---
        // `async` 关键字表明这是一个异步函数，它可以在执行过程中被“暂停”。
        // `await` 关键字用在调用异步函数的地方，表示“暂停”当前代码的执行，直到异步函数返回结果。
        
        print("\n[1] 调用单个异步函数:")
        let photo = await downloadPhoto(named: "照片1.jpg")
        print("已下载: \(photo)")
        
        // --- 2. 同时执行多个异步任务 ---
        // 如果我们像下面这样写，三个下载会一个接一个地执行，效率很低。
        /*
        let photo1 = await downloadPhoto(named: "photo1.jpg")
        let photo2 = await downloadPhoto(named: "photo2.jpg")
        let photo3 = await downloadPhoto(named: "photo3.jpg")
        */
        
        // 为了让它们同时开始，我们可以使用 `async let`
        print("\n[2] 使用 'async let' 并发调用多个异步函数:")
        async let firstPhoto = downloadPhoto(named: "图片_001.jpg")
        async let secondPhoto = downloadPhoto(named: "图片_002.jpg")
        async let thirdPhoto = downloadPhoto(named: "图片_003.jpg")
        
        // 当我们在这里使用 `await` 时，程序会暂停，直到所有三个下载都完成。
        let photos = await [firstPhoto, secondPhoto, thirdPhoto]
        print("已下载所有照片: \(photos)")
        
        
        // --- 3. 任务组 (Task Group) ---
        // 当你需要处理一个动态数量的并发任务时，任务组非常有用。
        print("\n[3] 使用任务组处理动态数量的任务:")
        let photoNames = ["巴黎.jpg", "伦敦.png", "东京.gif", "北京.tiff"]
        do {
            let processedPhotos = try await processPhotos(named: photoNames)
            print("从任务组处理完成的照片: \(processedPhotos)")
        } catch {
            print("处理照片时出错: \(error)")
        }
    }
}


// --- 模拟的异步函数 ---

// 这是一个模拟下载照片的异步函数。
// `async` 表示它是一个异步函数。
// `throws` 表示它可能会抛出错误。
func downloadPhoto(named name: String) async -> String {
    print("正在下载 '\(name)'...")
    // 使用 Task.sleep 来模拟耗时操作（如网络请求）
    // sleep(for:) 是一个新的异步 API
    try? await Task.sleep(for: .seconds(Double.random(in: 0.5...2.0)))
    print("完成下载 '\(name)'.")
    return "[\(name)]"
}

// 模拟处理照片的函数，它也可能是异步的
func processPhoto(_ photo: String) async -> String {
    print("正在处理 \(photo)...")
    try? await Task.sleep(for: .seconds(Double.random(in: 0.2...0.5)))
    return "已处理 \(photo)"
}


// --- 使用任务组的函数 ---
enum PhotoProcessingError: Error {
    case invalidFormat(String)
}

func processPhotos(named names: [String]) async throws -> [String] {
    // `withThrowingTaskGroup` 创建一个可以抛出错误的任务组。
    // `group` 参数可以用来向组里添加新的子任务。
    return try await withThrowingTaskGroup(of: String.self) { group in
        
        for name in names {
            // `addTask` 会立即开始执行闭包里的异步操作
            group.addTask {
                if name.hasSuffix(".tiff") {
                    // 我们可以从任务中抛出错误
                    throw PhotoProcessingError.invalidFormat(name)
                }
                let photo = await downloadPhoto(named: name)
                let processed = await processPhoto(photo)
                return processed
            }
        }
        
        // `group.next()` 会异步地等待下一个子任务完成并返回其结果。
        // 我们用一个数组来收集所有结果。
        var results: [String] = []
        for try await result in group {
            results.append(result)
        }
        
        // 任务组会在所有子任务都完成后自动退出。
        return results
    }
}
