//
//  ContentView.swift
//  unitConverter
//
//  Created by Arch on 2025/11/14.
//

import SwiftUI

struct ContentView: View {
    let models = ["长度","温度"]
    let lengthUnit = ["米","厘米","分米","毫米"]
    @State private var selectModel = "长度"
    @State private var inputNumberText = ""
    @State private var selectInputUnit = "米"
    @State private var selectOutputUnit = "分米"
    @State private var answer = "0.00"
    var body: some View {
        NavigationStack {
            Form {
                Picker("模式选择",selection: $selectModel) {
                    ForEach(models,id: \.self) {
                        model in Text(model)
                    }
                }
                .pickerStyle(.palette)
                .disabled(true)
                Section("请输入数据")  {
                    HStack {
                        TextField("数据",text: $inputNumberText)
                            .keyboardType(.decimalPad) // 数字键盘
                            .autocorrectionDisabled() // 禁用纠错
                        Picker(selection: $selectInputUnit, label: EmptyView()) {
                            ForEach(lengthUnit,id: \.self) {
                                Text($0)
                            }
                        }
                    }
                    HStack {
                        Text(answer)
                        Spacer()
                        Picker(selection: $selectOutputUnit, label: EmptyView()) {
                            ForEach(lengthUnit,id: \.self) {
                                Text($0)
                            }
                        }
                    }
                }
               
                
            }
            .navigationTitle("单位转换器")
            .onChange(of: inputNumberText) {calculateLength()}
            .onChange(of: selectInputUnit) {calculateLength()}
            .onChange(of: selectOutputUnit) {calculateLength()}
            .onAppear{calculateLength()}
            
        }
    }
    private func calculateLength() {
        guard let inputValue = Double(inputNumberText) else {
            answer = "0.0"
            return
        }
        
        let meters : Double
        switch selectInputUnit {
        case "米": meters = inputValue
        case "分米": meters = inputValue/10
        case "厘米": meters = inputValue / 100
        case "毫米": meters = inputValue / 1000
        default: meters = 0.0
        }
        let result: Double
        switch selectOutputUnit {
        case "米": result = meters
        case "分米": result = meters * 10 // 1 米 = 10 分米
        case "厘米": result = meters * 100 // 1 米 = 100 厘米
        case "毫米": result = meters * 1000 // 1 米 = 1000 毫米
        default: result = 0
        }
        answer = String(format: "%.4f", result)
    }
}

#Preview {
    ContentView()
}
