// --- 3. 循环语句 ---

// For-In 循环
// 遍历数组
let names = ["Anna", "Alex", "Brian", "Jack"]
for name in names {
    print("Hello, \(name)!")
}

// 遍历字典
let numberOfLegs = ["spider": 8, "ant": 6, "cat": 4]
for (animalName, legCount) in numberOfLegs {
    print("\(animalName)s have \(legCount) legs")
}

// 遍历数字范围
for index in 1...5 { // ... 是闭区间操作符
    print("\(index) times 5 is \(index * 5)")
}

// 如果你不需要用到区间内的值，可以使用 `_`
let base = 3
let power = 10
var answer = 1
for _ in 1...power {
    answer *= base
}
print("\(base) to the power of \(power) is \(answer)")

// While 循环
// 在循环开始前检查条件
var number = 5
while number > 0 {
    print(number)
    number -= 1
}

// Repeat-While 循环
// 相当于其他语言的 do-while，在循环结束后检查条件，保证循环体至少执行一次。
var count = 0
repeat {
    print("This will be printed at least once")
    count += 1
} while count < 0
