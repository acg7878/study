//
//  test.swift
//  GuessTheFlag
//
//  Created by Arch on 2025/11/14.
//

import SwiftUI

struct testView : View {
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
    @State private var currentValue = Int.random(in: 0...2)
    @State private var score = "0.0"
    @State private var isAlert = false
    @State private var alertTitle = ""
    var body: some View {
        ZStack {
            LinearGradient(gradient: Gradient(colors: [.blue, .black]), startPoint: .top, endPoint: .bottom)
                .ignoresSafeArea()
            VStack (spacing: 30) {
                Spacer()
                Text("猜国家")
                    .foregroundStyle(.white)
                    .font(.largeTitle)
                Spacer()
                Text("请选择\(countries[currentValue])的国旗")
                    .font(.title2)
                    .foregroundStyle(.white)
                    .bold()
                Spacer()
                ForEach(0..<3) {number in
                    Button(action: {tip()}) {
                        Text(countryEmojis[countries[number]] ?? "?")
                            .font(.system(size: 80))
                            .shadow(radius: 5)
                            .frame(width: 120, height: 120)
                    }
                }
                Spacer()
                Text("得分：\(score)")
                    .foregroundStyle(.white)
                    .font(.title)
                    .bold()
            }
        }
        .alert(alertTitle == "正确" ? "回答正确" : "回答错误", isPresented: $isAlert) {
            Button("继续") {
                
            }
        }
        
    }
    
    func tip() {
        
    }
    
}

#Preview {
    testView()
}
