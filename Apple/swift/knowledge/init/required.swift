class Person {
    let name: String
    let age: Int

    // 必须实现 required 初始化器
    required init(name: String, age: Int) {
        self.name = name
        self.age = age
    }
}

class Student: Person {
    let school: String

    // 自定义的指定初始化器
    init(name: String, age: Int, school: String) {
        self.school = school
        super.init(name: name, age: age)
    }

    // 必须实现父类的 required 初始化器
    required init(name: String, age: Int) {
        self.school = "Unknown"
        super.init(name: name, age: age)
    }
}