// 未命名元组
let tuple1 = (1,2,3)

// 命名元组
let tuple2 = (name:"yjk",age:18)

// 访问
let m_1 = tuple1.0
let m_2 = tuple1.1
let m_age = tuple2.age
let m_name = tuple2.name
print("m_1:",m_1,"m_2:",m_2,"m_age:",m_age,"m_name:",m_name)

// 解包
let (name,age) = tuple2
print("name:",name,"age:",age)

// 部分解包
let (_,age2) = tuple2
print("age2:",age2)

// 命名解包
let(name:rename,age:reage) = tuple2
print("rename:",rename,"reage:",reage)