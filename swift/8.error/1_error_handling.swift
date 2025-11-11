// --- Swift 错误处理学习 ---

import Foundation

// --- 1. 定义错误类型 ---
// 在 Swift 中，错误通常用一个遵守 `Error` 协议的枚举来表示。
// 这让我们可以清晰地分类和识别不同的错误情况。

enum VendingMachineError: Error {
    case invalidSelection
    case insufficientFunds(coinsNeeded: Int)
    case outOfStock
}


// --- 2. 抛出错误 (Throwing Errors) ---
// 我们创建一个函数，它可能会失败并抛出一个我们上面定义的错误。
// 在函数声明的参数列表后，使用 `throws` 关键字来表明这个函数可以抛出错误。

struct Item {
    var price: Int
    var count: Int
}

class VendingMachine {
    var inventory = [
        "Candy Bar": Item(price: 12, count: 7),
        "Chips": Item(price: 10, count: 4),
        "Pretzels": Item(price: 7, count: 11)
    ]
    var coinsDeposited = 0

    func vend(itemNamed name: String) throws {
        // 使用 guard 来检查各种可能失败的条件
        
        guard let item = inventory[name] else {
            throw VendingMachineError.invalidSelection
        }

        guard item.count > 0 else {
            throw VendingMachineError.outOfStock
        }

        guard coinsDeposited >= item.price else {
            let coinsNeeded = item.price - coinsDeposited
            throw VendingMachineError.insufficientFunds(coinsNeeded: coinsNeeded)
        }

        // 如果所有检查都通过，交易成功
        coinsDeposited -= item.price
        var newItem = item
        newItem.count -= 1
        inventory[name] = newItem

        print("Dispensing \(name)")
    }
}


// --- 3. 处理错误 (Handling Errors) ---
// 当你调用一个可以抛出错误的函数时，你必须使用 `try` 关键字，
// 并且把它放在一个 `do-catch` 语句块中。

let favoriteSnacks = [
    "Alice": "Chips",
    "Bob": "Licorice",
    "Eve": "Pretzels",
]

func buyFavoriteSnack(person: String, vendingMachine: VendingMachine) {
    let snackName = favoriteSnacks[person] ?? "Candy Bar"
    
    print("\(person) is trying to buy a \(snackName)...")
    
    // `do` 块包含了可能会抛出错误的代码
    do {
        try vendingMachine.vend(itemNamed: snackName)
        print("Success! Enjoy your snack, \(person).")
    } catch VendingMachineError.invalidSelection {
        print("Invalid Selection.")
    } catch VendingMachineError.outOfStock {
        print("Sorry, out of stock.")
    } catch VendingMachineError.insufficientFunds(let coinsNeeded) {
        print("Insufficient funds. Please insert an additional \(coinsNeeded) coins.")
    } catch {
        // 一个通用的 catch 块，可以捕获任何其他类型的错误
        print("An unexpected error occurred: \(error)")
    }
    print("---")
}

var vendingMachine = VendingMachine()
vendingMachine.coinsDeposited = 20

buyFavoriteSnack(person: "Alice", vendingMachine: vendingMachine)
buyFavoriteSnack(person: "Bob", vendingMachine: vendingMachine)
buyFavoriteSnack(person: "Eve", vendingMachine: vendingMachine)


// --- 4. 转换错误为可选值 (try?) ---
// 如果你只关心操作是否成功，而不关心具体的错误原因，可以使用 `try?`。
// 如果函数成功执行，`try?` 会返回一个包含函数返回值（如果是 void 则为 `()`) 的可选值。
// 如果函数抛出错误，`try?` 会返回 `nil`。

let result: ()? = try? vendingMachine.vend(itemNamed: "Chips")
if result != nil {
    print("Vending using try? was successful.")
} else {
    print("Vending using try? failed.")
}


// --- 5. 禁用错误传递 (try!) ---
// 如果你 100% 确定一个抛出函数在运行时绝对不会抛出错误，你可以使用 `try!`。
// 这和强制解包可选值的 `!` 类似：如果函数真的抛出了错误，你的程序会直接崩溃。
// **应谨慎使用。**
// let _ = try! vendingMachine.vend(itemNamed: "This item does not exist") // 会导致崩溃


// --- 6. defer 语句 ---
// `defer` 语句块中的代码，会在当前代码块退出（无论是正常返回还是因为抛出错误）之前被执行。
// 它非常适合用来做一些清理工作，比如关闭文件、释放资源等。

func processFile(path: String) throws {
    print("Opening file at \(path)...")
    // 假设这里打开了文件
    
    defer {
        // 无论函数是成功返回还是抛出错误，这句都会在最后执行。
        print("Closing file.")
    }
    
    print("Processing file...")
    if path.isEmpty {
        throw NSError(domain: "TestError", code: 1, userInfo: nil)
    }
    print("File processing complete.")
}

print("\n--- Testing defer ---")
try? processFile(path: "my_document.txt")
print("---")
try? processFile(path: "")
