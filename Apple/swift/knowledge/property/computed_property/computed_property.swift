import Foundation

struct Square {
    var sideLength: Double

    var area: Double {
        get { sideLength * sideLength }
        set {
            sideLength = sqrt(newValue)
            // 写下面的代码会导致无限递归，因为修改又会触发set代码块
            // 计算属性不存储值！这里赋值有问题的
            //self.area = newValue
        }
    }
}

var square = Square(sideLength: 5)
print(square.area)

square.area = 36
print(square.sideLength)