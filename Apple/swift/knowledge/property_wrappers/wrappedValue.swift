// 属性包装器 是一个遵循 PropertyWrapper 协议的结构体、类或枚举。
// 它的核心作用是 “包装” 一个属性，将该属性的 存储 和 访问逻辑 委托给包装器本身。

// 声明包装器，只对struct修饰
// 以一个默认值包装器为例
@propertyWrapper
struct DefaultValue {
  // 包装器核心是定义wrappedValue
  private var defaultValue: String
  // 存储属性的真实值
  private var _wrappedValue: String

  // wrappedValue是属性包装器的必需属性
  var wrappedValue: String {
    get { _wrappedValue }
    set {
      _wrappedValue = newValue.isEmpty ? defaultValue : newValue
    }
  }

  init(defaultValue: String) {
    self.defaultValue = defaultValue
    self._wrappedValue = defaultValue
  }
}

struct Test {
  @DefaultValue(defaultValue: "未知手机号") var number: String
}

var test = Test()
print(test.number)
