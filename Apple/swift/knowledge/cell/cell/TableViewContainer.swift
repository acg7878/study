//
//  TableViewContainer.swift
//  cell
//
//  UITableView Cell 复用示例
//

import UIKit
import SwiftUI

// MARK: - 数据模型
struct CellData {
    let id: Int
    let title: String
    let detail: String
    let iconName: String
}

// MARK: - UITableView 容器（用于在 SwiftUI 中使用）
struct TableViewContainer: UIViewControllerRepresentable {
    
    func makeUIViewController(context: Context) -> TableViewController {
        return TableViewController()
    }
    
    func updateUIViewController(_ uiViewController: TableViewController, context: Context) {
        // 更新逻辑
    }
}

// MARK: - TableViewController
class TableViewController: UIViewController {
    
    private var tableView: UITableView!
    private var data: [CellData] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupTableView()
        generateData()
    }
    
    // MARK: - 设置 TableView
    private func setupTableView() {
        tableView = UITableView(frame: view.bounds, style: .plain)
        tableView.delegate = self
        tableView.dataSource = self
        
        // 🔑 关键步骤 1：注册 Cell（告诉 tableView 使用哪种 cell）
        tableView.register(CustomTableViewCell.self, 
                          forCellReuseIdentifier: "CustomCell")
        
        // 设置行高
        tableView.rowHeight = UITableView.automaticDimension
        tableView.estimatedRowHeight = 80
        
        view.addSubview(tableView)
        tableView.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            tableView.topAnchor.constraint(equalTo: view.topAnchor),
            tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            tableView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            tableView.bottomAnchor.constraint(equalTo: view.bottomAnchor)
        ])
    }
    
    // MARK: - 生成测试数据
    private func generateData() {
        let icons = ["star.fill", "heart.fill", "book.fill", "music.note", 
                    "camera.fill", "gamecontroller.fill", "airplane", "car.fill"]
        
        for i in 0..<1000 {  // 生成 1000 条数据，测试复用效果
            let iconIndex = i % icons.count
            data.append(CellData(
                id: i,
                title: "项目 \(i + 1)",
                detail: "这是第 \(i + 1) 个项目的详细描述。Cell 复用机制确保即使有 1000 条数据，也只会创建屏幕可见数量的 cell。",
                iconName: icons[iconIndex]
            ))
        }
    }
}

// MARK: - UITableViewDataSource
extension TableViewController: UITableViewDataSource {
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return data.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        // 🔑 关键步骤 2：从复用池获取 cell（或创建新 cell）
        let cell = tableView.dequeueReusableCell(withIdentifier: "CustomCell", 
                                                for: indexPath) as! CustomTableViewCell
        
        // 🔑 关键步骤 3：每次都必须更新 cell 内容（避免显示旧数据）
        let item = data[indexPath.row]
        cell.configure(title: item.title, 
                      detail: item.detail, 
                      iconName: item.iconName)
        
        // 打印日志，观察复用情况
        if indexPath.row < 20 || indexPath.row % 100 == 0 {
            print("📱 配置 Cell for row \(indexPath.row)")
        }
        
        return cell
    }
}

// MARK: - UITableViewDelegate
extension TableViewController: UITableViewDelegate {
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        let item = data[indexPath.row]
        print("✅ 选中了：\(item.title)")
        
        // 显示提示
        let alert = UIAlertController(title: "选中项目", 
                                     message: item.title, 
                                     preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "确定", style: .default))
        present(alert, animated: true)
    }
    
    func scrollViewDidScroll(_ scrollView: UIScrollView) {
        // 可以在这里观察滚动时的复用情况
    }
}

