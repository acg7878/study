//
//  ContentView.swift
//  cell
//
//  Cell 复用示例 - 主视图
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        NavigationView {
            VStack(spacing: 0) {
                // 说明信息
                VStack(alignment: .leading, spacing: 8) {
                    Text("Cell 复用示例")
                        .font(.title2)
                        .fontWeight(.bold)
                    
                    Text("• 1000 条数据，但只创建屏幕可见的 cell")
                        .font(.caption)
                        .foregroundColor(.secondary)
                    
                    Text("• 滚动时观察控制台，查看 cell 复用情况")
                        .font(.caption)
                        .foregroundColor(.secondary)
                    
                    Text("• prepareForReuse() 会在复用前重置 cell 状态")
                        .font(.caption)
                        .foregroundColor(.secondary)
                }
                .padding()
                .frame(maxWidth: .infinity, alignment: .leading)
                .background(Color(.systemGray6))
                
                // UITableView（使用 UIKit）
                TableViewContainer()
            }
            .navigationTitle("Cell 复用")
            .navigationBarTitleDisplayMode(.inline)
        }
    }
}

#Preview {
    ContentView()
}
