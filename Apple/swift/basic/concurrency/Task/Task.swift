import Foundation


// top-level task
Task {
    print("top-level task")
}

// 异步上下文创建Task
// 父 Task 会隐式等待所有子 Task 完成。
// 如果父 Task 提前完成或被取消，其子 Task 也可能会被取消。
func doSomething() async {
    print("Parent task started")

    let childTask = Task {
        print("Child task started")
        return 42
    }

    // value：子任务的返回值
    let result = await childTask.value
    print("Child task finished, result: \(result)")
    print("Parent task finished")
}

Task {
    await doSomething()
}


RunLoop.main.run(until: Date(timeIntervalSinceNow: 1))