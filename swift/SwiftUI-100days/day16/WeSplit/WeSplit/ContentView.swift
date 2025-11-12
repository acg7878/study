//
//  ContentView.swift
//  WeSplit
//
//  Created by Arch on 2025/11/12.
//

import SwiftUI

struct ContentView: View {
    @State var count = 0;
    @State var name = ""
    var body : some View {
        NavigationStack {
            Form {
                Text("Hello,World")
                Section {
                    Text("Test")
                    Text("Test")
                    Text("Test")
                }
                Button("Tap Count: \(count)") {
                    count+=1
                }
                
                // 双向绑定
                TextField("Enter your name",text: $name)
                
                // 循环中创建视图
                ForEach(0..<10) { number in
                        Text("Row \(number)")
                }
            }
            .navigationTitle("SwiftUI")
            .navigationBarTitleDisplayMode(.inline)
        }
    }
}

#Preview {
    ContentView()
}
