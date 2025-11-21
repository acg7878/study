// 定义无参函数
func printHello() {
    print("hello!")
}

// 定义有参函数
func printName(name: String) {
    print("hello!\(name)")
}

// 定义有返回值函数
func echo(str:String) -> String {
    return str;
}

// inout
func changeValue( num:inout Int) {
    num = num + 1
}

// 调用
printHello()
printName(name: "man")
print(echo(str: "echo!"))
var number = 1
changeValue(num: &number)
print(number)