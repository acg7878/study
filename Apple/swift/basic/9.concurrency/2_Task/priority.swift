import Foundation
// 优先级是一个提示，不保证执行顺序，但会影响调度器的决策

// 低优先级任务
Task(priority: .low) {
    print("Low priority task is running.")
}

// 高优先级任务
Task(priority: .high) {
    print("High priority task is running.")
}

// 优先级从高到低有：
// .userInitiated 用户交互任务，需要立即响应
// .userInteractive 用户交互任务，需要立即响应
// .default 默认优先级
// .utility 实用任务，需要长时间执行
// .background 后台任务，不需要立即响应

RunLoop.main.run(until: Date(timeIntervalSinceNow: 1))