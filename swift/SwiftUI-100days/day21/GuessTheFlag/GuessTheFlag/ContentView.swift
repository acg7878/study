//
//  ContentView.swift
//  GuessTheFlag
//
//  Created by Arch on 2025/11/14.
//

import SwiftUI

struct ContentView: View {
    // 国旗数组：用「国家名称-国旗emoji」的字典，方便对应
    private let countryEmojis: [String: String] = [
        "Estonia": "🇪🇪",    // 爱沙尼亚
        "France": "🇫🇷",     // 法国
        "Germany": "🇩🇪",    // 德国
        "Ireland": "🇮🇪",    // 爱尔兰
        "Italy": "🇮🇹",      // 意大利
        "Nigeria": "🇳🇬",    // 尼日利亚
        "Poland": "🇵🇱",     // 波兰
        "Spain": "🇪🇸",      // 西班牙
        "UK": "🇬🇧",         // 英国
        "Ukraine": "🇺🇦",    // 乌克兰
        "US": "🇺🇸"          // 美国
    ]
    
    // 国家名称数组（用于随机和判断）
    @State private var countries = ["Estonia", "France", "Germany", "Ireland", "Italy", "Nigeria", "Poland", "Spain", "UK", "Ukraine", "US"].shuffled()
    
    // 正确答案的索引（0-2 之间随机）
    @State private var correctAnswer = Int.random(in: 0...2)
    
    // 弹窗相关状态
    @State private var showingScore = false
    @State private var scoreTitle = ""
    @State private var userScore = 0
    
    var body: some View {
        ZStack {
            // 背景渐变
            LinearGradient(gradient: Gradient(colors: [.blue, .black]), startPoint: .top, endPoint: .bottom)
                .ignoresSafeArea()
            
            VStack(spacing: 30) {
                Spacer()
                
                // 游戏标题
                Text("猜猜国旗")
                    .font(.largeTitle)
                    .foregroundStyle(.white)
                
                // 提示文本：显示要猜的国家名称（让用户知道目标）
                Text("点击 \(countries[correctAnswer]) 的国旗")
                    .foregroundStyle(.white)
                    .font(.title2)
                    .bold()
                
                Spacer()
                
                // 国旗按钮（用 emoji 替代图片）
                ForEach(0..<3) { number in
                    Button(action: {
                        flagTapped(number)
                    }) {
                        // 核心修改：用字典获取国家对应的国旗 emoji
                        Text(countryEmojis[countries[number]] ?? "❓")
                            .font(.system(size: 80)) // 调整 emoji 大小（可自定义）
                            .shadow(radius: 5) // 阴影提升质感
                            .frame(width: 120, height: 120) // 固定按钮尺寸，避免 emoji 大小不一致
                    }
                }
                
                Spacer()
                
                // 得分显示
                Text("当前得分: \(userScore)")
                    .foregroundStyle(.white)
                    .font(.title)
                    .bold()
                
                Spacer()
            }
            .padding()
        }
        // 得分弹窗
        .alert(scoreTitle, isPresented: $showingScore) {
            Button("继续", action: askQuestion)
        } message: {
            VStack {
                Text(scoreTitle == "正确" ? "回答正确！" : "回答错误～")
                    .foregroundStyle(scoreTitle == "正确" ? .green : .red)
                // 错误时显示正确答案的 emoji（优化体验）
                if scoreTitle == "错误" {
                    Text("正确答案是：\(countryEmojis[countries[correctAnswer]] ?? "❓")")
                        .font(.title)
                        .padding(.top, 10)
                }
                Text("当前得分: \(userScore)")
                    .padding(.top, 10)
            }
        }
    }
    
    // 点击国旗后的判断逻辑
    func flagTapped(_ number: Int) {
        if number == correctAnswer {
            scoreTitle = "正确"
            userScore += 10
        } else {
            scoreTitle = "错误"
            // 可选：错误扣 5 分（取消注释即可）
            // userScore = max(0, userScore - 5)
        }
        showingScore = true
    }
    
    // 重置游戏
    func askQuestion() {
        countries.shuffle()
        correctAnswer = Int.random(in: 0...2)
    }
}

// 预览视图
#Preview {
    ContentView()
}
