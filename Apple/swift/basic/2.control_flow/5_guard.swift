func printStr(name: String?) {
    guard let test = name else {
        print("name is nil!")
        return
    }
    print("hello,\(test)")
    
}

printStr(name: "man")
printStr(name: nil)