import Foundation

// weak只能用于引用类型
// AnyObject限制该协议只能由引用类型（class）实现
protocol FileDownloaderDelegate: AnyObject {
    func downloader(_ downloader: FileDownloader, progressDidUpdate progress: Float)
    func downloader(_ downloader: FileDownloader, didFinishDownload filePath: String)
    // 可选实现：下载失败（通过扩展提供默认实现）
    func downloader(_ downloader: FileDownloader, didFailWithError error: Error)
}

extension FileDownloaderDelegate {
    func downloader(_ downloader: FileDownloader, didFailWithError error: Error) {
        print("【默认处理】下载失败：\(error.localizedDescription)")
    }
}

// 委托方（文件下载器：发起下载事件，委托外部处理结果）
class FileDownloader {
    weak var delegate: FileDownloaderDelegate?

    private let fileURL: String
    private var currentProgress: Float = 0.0

    init(fileURL: String) {
        self.fileURL = fileURL
    }

    // 开始下载（模拟分段下载）
    func startDownload() {
        print("开始下载文件：\(fileURL)")

        for i in 1...10 {
            DispatchQueue.global().asyncAfter(deadline: .now() + Double(i) * 0.5) { [weak self] in
                guard let self = self else { return }
                self.currentProgress = Float(i) / 10.0
                self.delegate?.downloader(self, progressDidUpdate: self.currentProgress)
                if self.currentProgress == 1.0 {
                    let filePath = "/Documents/\(UUID().uuidString).txt"
                    self.delegate?.downloader(self, didFinishDownload: filePath)
                }
            }
        }

        let randomFail = Int.random(in: 1...100)
        if randomFail == 50 {
            DispatchQueue.global().asyncAfter(deadline: .now() + 2.0) { [weak self] in
                guard let self = self else { return }
                let error = NSError(
                    domain: "DownloadError", code: -1001,
                    userInfo: [NSLocalizedDescriptionKey: "网络超时"])
                self.delegate?.downloader(self, didFailWithError: error)
            }
        }
    }
}

class DownloadManager: FileDownloaderDelegate {
    private var downloadTasks: [FileDownloader] = []
    func addDownloadTask(fileURL: String) {
        let downloader = FileDownloader(fileURL: fileURL)
        downloader.delegate = self  // 绑定委托关系
        downloadTasks.append(downloader)
        downloader.startDownload()
    }

    func downloader(_ downloader: FileDownloader, progressDidUpdate progress: Float) {
        let progressText = String(format: "%.0f%%", progress * 100)
        print("【下载进度】\(progressText)")
    }

    func downloader(_ downloader: FileDownloader, didFinishDownload filePath: String) {
        print("【下载完成】文件已保存到：\(filePath)")
        removeDownloadTask(downloader: downloader)
    }

    // 可选重写：自定义下载失败处理
    func downloader(_ downloader: FileDownloader, didFailWithError error: Error) {
        print("【自定义处理】下载失败：\(error.localizedDescription)，准备重试...")
        DispatchQueue.global().asyncAfter(deadline: .now() + 3.0) {
            downloader.startDownload()
        }
    }

    // 移除完成/失败的下载任务
    private func removeDownloadTask(downloader: FileDownloader) {
        if let index = downloadTasks.firstIndex(where: { $0 === downloader }) {
            downloadTasks.remove(at: index)
            print("【任务管理】已移除完成的下载任务，剩余任务数：\(downloadTasks.count)")
        }
    }
}

let manager = DownloadManager()
manager.addDownloadTask(fileURL: "https://example.com/large_file.zip")
// manager.addDownloadTask(fileURL: "https://example.com/small_file.txt")

RunLoop.main.run(until: Date().addingTimeInterval(20))
