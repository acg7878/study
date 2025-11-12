import Foundation

// MARK: 核心任务：从 10^10 减到 0（纯计算，无阻塞）
/// 分段执行减法（避免单个任务占用过多资源）
/// - Parameter start: 起始值
/// - Parameter end: 结束值（0）
func subtractTask(start: UInt64, end: UInt64) {
    var value = start
    while value > end {
        value -= 1
    }
}

// MARK: 1. 单线程执行（串行，无并发）
func testSingleThread() -> TimeInterval {
    print("=== 单线程执行：100亿次减法 ===")
    let start = Date()
    
    // 单个任务从头减到尾
    subtractTask(start: 10_000_000_000, end: 0)
    
    let duration = Date().timeIntervalSince(start)
    print("单线程耗时：\(duration.roundTo(2))s\n")
    return duration
}

// MARK: 2. Swift 并发（TaskGroup，按 CPU 核心数拆分任务）
func testSwiftConcurrency() async -> TimeInterval {
    print("=== Swift 并发（TaskGroup）：100亿次减法 ===")
    let start = Date()
    let totalCount: UInt64 = 10_000_000_000
    
    // 按 CPU 核心数拆分任务（避免过度并发）
    let coreCount = ProcessInfo.processInfo.activeProcessorCount
    let chunkSize = totalCount / UInt64(coreCount) // 每个任务的执行量
    
    await withTaskGroup(of: Void.self) { group in
        for i in 0..<coreCount {
            // 计算每个任务的起始值和结束值
            let taskStart = chunkSize * UInt64(i) + 1
            let taskEnd: UInt64 = (i == coreCount - 1) ? totalCount : chunkSize * UInt64(i + 1)
            
            group.addTask {
                subtractTask(start: taskEnd, end: taskStart) // 从大到小减
            }
        }
    }
    
    let duration = Date().timeIntervalSince(start)
    print("Swift 并发（\(coreCount) 个任务）耗时：\(duration.roundTo(2))s\n")
    return duration
}

// MARK: 3. 传统多线程（DispatchQueue，并行队列）
func testDispatchQueueConcurrency() -> TimeInterval {
    print("=== 传统多线程（DispatchQueue）：100亿次减法 ===")
    let start = Date()
    let totalCount: UInt64 = 10_000_000_000
    let coreCount = ProcessInfo.processInfo.activeProcessorCount
    let chunkSize = totalCount / UInt64(coreCount)
    
    // 创建并行队列（QoS：用户交互级，匹配计算任务优先级）
    let queue = DispatchQueue(label: "com.test.concurrency", qos: .userInitiated, attributes: .concurrent)
    let group = DispatchGroup()
    
    for i in 0..<coreCount {
        let taskStart = chunkSize * UInt64(i) + 1
        let taskEnd: UInt64 = (i == coreCount - 1) ? totalCount : chunkSize * UInt64(i + 1)
        
        queue.async(group: group) {
            subtractTask(start: taskEnd, end: taskStart)
        }
    }
    
    group.wait() // 等待所有任务完成（阻塞当前线程，仅用于测试对比）
    let duration = Date().timeIntervalSince(start)
    print("DispatchQueue 并发（\(coreCount) 个任务）耗时：\(duration.roundTo(2))s\n")
    return duration
}

// MARK: 辅助工具：保留2位小数
extension Double {
    func roundTo(_ places: Int) -> Double {
        let divisor = pow(10.0, Double(places))
        return (self * divisor).rounded() / divisor
    }
}

@main
struct Main {
    static func main() async {
        // MARK: 执行入口 + 结果对比
        // 执行三种方式（顺序执行，避免互相干扰）
        let singleThreadTime = testSingleThread()
        let dispatchQueueTime = testDispatchQueueConcurrency()
        let swiftConcurrencyTime = await testSwiftConcurrency()

        // 打印结果
        print("\n--- 性能对比 ---")
        print("计算任务：\(10_000_000_000 / 1_000_000_000) 亿次减法，分 \(ProcessInfo.processInfo.activeProcessorCount) 组")
        print("单线程：\(singleThreadTime.roundTo(2))s（基准）")
        print("Swift 并发：\(swiftConcurrencyTime.roundTo(2))s（提速：\((singleThreadTime / swiftConcurrencyTime).roundTo(2)) 倍）")
        print("DispatchQueue 并发：\(dispatchQueueTime.roundTo(2))s（提速：\((singleThreadTime / dispatchQueueTime).roundTo(2)) 倍）")
    }
}