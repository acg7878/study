//
//  ContentView.swift
//  GuessTheFlag
//
//  Created by Arch on 2025/11/14.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
// 1.
//        ZStack {
//            VStack(spacing: 0) {
//                Color.red
//                Color.blue
//            }
//
//            Text("Your content")
//                .foregroundStyle(.secondary)
//                .padding(50)
//                .background(.ultraThickMaterial)
//        }
//        .ignoresSafeArea()
        
        // 2. 图片、按钮
        
        // .destructive「功能角色标识」：表示这个按钮是破坏性的
        Button("删除",role: .destructive) {
            print("删除")
        }
        
        VStack {
            Button("Button 1") { }
                .buttonStyle(.bordered)
            Button("Button 2", role: .destructive) { }
                .buttonStyle(.bordered)
            Button("Button 3") { }
                //.tint(.mint)
                // ⬆️使用统一的主题色
                .buttonStyle(.borderedProminent)
            Button("Button 4", role: .destructive) { }
                .buttonStyle(.borderedProminent)
            Button {
                // 1. 动作闭包（Action）：按钮被点击时执行的逻辑
                print("Button was tapped")
            } label: {
                // 标签闭包（Label）：按钮的可视化外观
                Text("Tap me!")
                    .padding()
                    .foregroundStyle(.white)
                    .background(.red)
            }
            Button {
                print("Edit button was tapped")
            } label: {
                Image(systemName: "pencil")
            }
            
            // 同时使用图标和字体
            Button("Edit", systemImage: "pencil") {
                print("Edit button was tapped")
            }
            
            Button {
                print("Edit button was tapped")
            } label: {
                Label("Edit", systemImage: "pencil")
                    .padding()
                    .foregroundStyle(.white)
                    .background(.red)
            }
        }
    }
}

#Preview {
    ContentView()
}
