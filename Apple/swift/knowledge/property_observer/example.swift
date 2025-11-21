class StepCounter {
    var totalSteps: Int = 0 {
        // willSet: 在值被存储之前调用
        // 默认参数名是 newValue，也可以自定义名称，如 willSet(myNewValue)
        willSet {
            print("--- willSet ---")
            print("当前值: \(totalSteps)")
            print("将要设置的新值: \(newValue)")
        }
        
        // didSet: 在值被存储之后立即调用
        // 默认参数名是 oldValue
        didSet {
            print("--- didSet ---")
            print("旧值: \(oldValue)")
            print("当前新值: \(totalSteps)")
            
            if totalSteps > oldValue {
                print("增加了 \(totalSteps - oldValue) 步")
            }
        }
    }
}

// 测试
let counter = StepCounter()
counter.totalSteps = 100
counter.totalSteps = 350

