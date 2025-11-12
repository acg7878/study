// empty
var array = [Int]()
print("array is empty:", array.isEmpty)
var array2: [Int] = []
print("array2 is empty:", array2.isEmpty)

// init<S>(_ elements: S) where S : Sequence, Self.Element == S.Element
// Sequence ： 可遍历的序列
let range = 0...3
let array3 = Array(range)
print("array3:", array3)

// init(
//     repeating repeatedValue: Element,
//     count: Int
// )
let array4 = Array(repeating: 0, count: 3)
print("array4:", array4)

// init(
//     unsafeUninitializedCapacity: Int,
//     initializingWith initializer: (inout UnsafeMutableBufferPointer<Element>, inout Int) throws -> Void
// ) rethrows
let numbers = Array(
    unsafeUninitializedCapacity: 5  // 预分配 5 个 Int 的内存
) { buffer, initializedCount in
    // buffer 是 UnsafeMutableBufferPointer<Int>，指向 5 个未初始化的 Int 内存
    for i in 0..<5 {
        buffer[i] = i  // 直接给内存赋值（初始化元素）
    }
    initializedCount = 5  // 明确告知：已初始化 5 个元素
}
