import Foundation

// Task的取消是协作式的
// 如果一个Task被取消，它会立即停止执行，并抛出CancellationError

let task = Task {
    do {
        for i in 1..<10 {
            try Task.checkCancellation()
            print("Task: \(i)")
            try await Task.sleep(nanoseconds: 1_000_000_000)
        }
        print("Task finished")
    } catch is CancellationError {
        print("Task cancelled")
    } catch {
        print("Task failed: \(error)")
    } 
}

Task {
    try await Task.sleep(nanoseconds: 3_000_000_000)
    task.cancel()
    print("Task cancelled by parent task")
}

RunLoop.main.run(until: Date(timeIntervalSinceNow: 5))