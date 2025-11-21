class Parent {
    var name: String
    
    init(name: String) {
        self.name = name
        print("✅ Parent init: \(name)")
    }
    
    deinit {
        print("❌ Parent deinit: \(name)")
    }
}

class Child: Parent {
    
    override init(name: String) {
        super.init(name: name)
        print("✅ Child init: \(name)")
    }

    deinit {
        print("❌ Child deinit: \(name)")
    }
}

// --- 测试代码 ---

func testDeinitOrder() {
    print("1. 创建实例")
    var person: Child? = Child(name: "TestObject")
    
    print("2. 准备释放实例")
    person = nil // 触发 deinit
    
    print("3. 实例已释放")
}

testDeinitOrder()

