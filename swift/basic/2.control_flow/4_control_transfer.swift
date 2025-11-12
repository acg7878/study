// --- 4. 控制转移语句 ---

// Continue
// 结束本次循环，直接进入下一次循环。
let puzzleInput = "great minds think alike"
var puzzleOutput = ""
let charactersToRemove: [Character] = ["a", "e", "i", "o", "u", " "]
for character in puzzleInput {
    if charactersToRemove.contains(character) {
        continue // 如果是元音或空格，就跳过，不添加到输出字符串
    }
    puzzleOutput.append(character)
}
print(puzzleOutput) // 输出 "grtmndsthnklk"

// Break
// 立即结束整个循环或 switch 语句。
let numberSymbol: Character = "三"
var possibleIntegerValue: Int?
switch numberSymbol {
case "1", "١", "一", "๑":
    possibleIntegerValue = 1
case "2", "٢", "二", "๒":
    possibleIntegerValue = 2
case "3", "٣", "三", "๓":
    possibleIntegerValue = 3
case "4", "٤", "四", "๔":
    possibleIntegerValue = 4
default:
    break // 对于不需要处理的 case，使用 break 明确跳过
}
