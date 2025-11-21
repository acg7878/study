class Person {
    let name: String
    let age: Int

    // 指定初始化器 (Designated Initializer)
    init(name: String, age: Int) {
        self.name = name
        self.age = age
    }

    // 便利初始化器 (Convenience Initializer)
    // 必须调用 self.init(横向代理)
    convenience init(name: String) {
        self.init(name: name, age: 18)
    }
}

class Student: Person {
    let school: String

    // 指定初始化器
    init(name: String, age: Int, school: String) {
        self.school = school
        super.init(name: name, age: age)
    }

    // 便利初始化器
    convenience init() {
        self.init(name: "Unknown", age: 0, school: "No School")
    }
}
