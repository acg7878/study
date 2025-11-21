// 计算一个大数组中每个元素的平方，然后将所有平方值相加

import Foundation

let chunkSize = 100  // 定义分块大小

func sumOfSquares(in array: [Int], range: Range<Int>) -> Int {
    let sum = array[range].reduce(0) { $0 + $1 * $1 }
    return sum
}

// 单线程计算函数
func syncSumOfSquares(in array: [Int]) -> Int {
    return sumOfSquares(in: array, range: 0..<array.count)
}


func concurrentSumOfSquares(in array: [Int]) async -> Int {
    // of: Int.self：任务组中的任务返回值类型是Int
    await withTaskGroup(of: Int.self) { group in
        var sum = 0
        // stride: 步长，从0开始，到array.count结束，步长为chunkSize
        for i in stride(from: 0, to: array.count, by: chunkSize) {
            let startIndex = i
            let endIndex = min(i + chunkSize, array.count)
            let chunkRange = startIndex..<endIndex
            group.addTask {
                return sumOfSquares(in: array, range: chunkRange)
            }
        }
        for await result in group {
            sum += result
        }
        return sum
    }
}
let largeArray = Array(0..<1000000)

Task {
    print("数组大小: \(largeArray.count), 分块大小: \(chunkSize)\n")

    // --- 多线程并发计算 ---
    print("--- 开始并发计算 ---")
    let startTimeConcurrent = Date()
    let resultConcurrent = await concurrentSumOfSquares(in: largeArray)
    let endTimeConcurrent = Date()
    let durationConcurrent = endTimeConcurrent.timeIntervalSince(startTimeConcurrent)
    print("--- 并发计算完成，结果: \(resultConcurrent), 耗时: \(durationConcurrent)秒 ---\n")


    // --- 单线程同步计算 ---
    print("--- 开始单线程计算 ---")
    let startTimeSync = Date()
    let resultSync = syncSumOfSquares(in: largeArray)
    let endTimeSync = Date()
    let durationSync = endTimeSync.timeIntervalSince(startTimeSync)
    print("--- 单线程计算完成，结果: \(resultSync), 耗时: \(durationSync)秒 ---")
}
RunLoop.main.run(until: Date(timeIntervalSinceNow: 2))
