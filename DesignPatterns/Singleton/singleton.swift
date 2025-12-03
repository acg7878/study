import Foundation

final class Singleton {
    static let shared = Singleton()
    private init() {
        print("Singleton initialized")
    }
}

let singleton = Singleton.shared
print(singleton)