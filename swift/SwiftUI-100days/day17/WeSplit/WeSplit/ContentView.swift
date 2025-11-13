//
//  ContentView.swift
//  WeSplit
//
//  Created by Arch on 2025/11/12.
//

import SwiftUI

struct ContentView: View {
    @State private var checkAmount = 0.0
    @State private var numberOfPeople = 10
    @State private var tipPercentage = 20
    @FocusState private var amountIsFocused: Bool
    
    let tipPercentages = [10, 20, 30, 40, 0]
    
    // 计算「总金额（含小费）」
    var grandTotal: Double {
        checkAmount + (checkAmount * Double(tipPercentage) / 100)
    }
    
    // 计算「每人应付金额」
    var totalPerPerson: Double {
        let peopleCount = Double(numberOfPeople)
        //print(peopleCount)
        return peopleCount > 0 ? grandTotal / peopleCount : 0
    }
    
    var body: some View {
        NavigationStack {
            Form {
                // 1. 输入总金额
                Section("请输入总金额捏") {
                    TextField("Amount", value: $checkAmount, format: .currency(code: Locale.current.currency?.identifier ?? "CNY"))
                        .keyboardType(.decimalPad)
                        .focused($amountIsFocused)
                }

                // 2. 显示总金额（含小费）
                Section("总费用（含小费）") {
                    Text(grandTotal, format: .currency(code: Locale.current.currency?.identifier ?? "CNY"))
                        .fontWeight(.medium)
                }
                
                // 3. 人数选择 + 每人应付金额
                Section("分摊信息") {
                    Picker("人数", selection: $numberOfPeople) {
                        ForEach(1..<10,id: \.self) {
                            //let let_: () = print($0)
                            Text("\($0) 人")
                        }
                    }
                    //.pickerStyle(.navigationLink)
                    
                    // 明确标注「每人应付」
                    HStack {
                        Text("每人应付：")
                        Spacer()
                        Text(totalPerPerson, format: .currency(code: Locale.current.currency?.identifier ?? "CNY"))
                            .fontWeight(.bold)
                    }
                }
                
                // 4. 小费选择
                Section("给我多少小费呢你小子？") {
                    Picker("Tip Percentage", selection: $tipPercentage) {
                        ForEach(tipPercentages, id: \.self) {
                            Text($0 == 0 ? "无小费" : "\($0, format: .percent)")
                        }
                    }
                    .pickerStyle(.segmented)
                }
            }
            .navigationTitle("小费")
            //.toolbar()
            .onTapGesture {
                amountIsFocused = false
            }
        }
    }
}

#Preview {
    ContentView()
}
