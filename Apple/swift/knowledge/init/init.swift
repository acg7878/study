class Person {
    let name: String
    let age: Int

    init(name: String, age: Int) {
        self.name = name
        self.age = age
    }
}

class Student: Person {
    let school: String

    init(name: String, age: Int, school: String) {
        self.school = school
        super.init(name: name, age: age)
    }
}