protocol NetworkAuth {
    func getAuth()
    func postAuth()
    func downloadAuth()
}

class NetworkAuthProxy: NetworkAuth {
    private lazy var networkAuthController: NetworkAuthController = {
        print("初始化 NetworkAuthController...")
        return NetworkAuthController()
    }()

    func getAuth() {
        print("🔒 Proxy: 检查 GET 权限...")
        if hasPermission(for: .get) {
            networkAuthController.getAuth()
            print("✅ Proxy: GET 请求完成")
        } else {
            print("❌ Proxy: 无权限执行 GET")
        }
    }

    func postAuth() {
        print("🔒 Proxy: 检查 POST 权限...")
        if hasPermission(for: .post) {
            networkAuthController.postAuth()
            print("✅ Proxy: POST 请求完成")
        } else {
            print("❌ Proxy: 无权限执行 POST")
        }
    }

    func downloadAuth() {
        print("🔒 Proxy: 检查 DOWNLOAD 权限...")
        if hasPermission(for: .download) {
            networkAuthController.downloadAuth()
            print("✅ Proxy: DOWNLOAD 请求完成")
        } else {
            print("❌ Proxy: 无权限执行 DOWNLOAD")
        }
    }

    private func hasPermission(for method: HTTPMethod) -> Bool {
        return true
    }

    private enum HTTPMethod {
        case get, post, download
    }
}

class NetworkAuthController {
    func getAuth() {
        print("NetworkAuthController: you can use get command!")
    }

    func postAuth() {
        print("NetworkAuthController: you can use post command!")
    }

    func downloadAuth() {
        print("NetworkAuthController: you can use download command!")
        print("NetworkAuthController: download start!")
    }
}

let proxy = NetworkAuthProxy()
proxy.getAuth()
proxy.downloadAuth()
