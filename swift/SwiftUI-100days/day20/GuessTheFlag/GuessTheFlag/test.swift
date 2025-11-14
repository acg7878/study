//
//  test.swift
//  GuessTheFlag
//
//  Created by Arch on 2025/11/14.
//

import SwiftUI

struct testView : View {
    @State private var showingAlert = false
    @State private var showingAlert2 = false
    var body : some View {
        
        Button("Show Alert") {
            showingAlert = true
        }
        .alert("Important message", isPresented: $showingAlert) {
            Button("OK") { }
            Button("Cancel", role: .cancel) { }
            Button("Delete", role: .destructive){}
        }
        
        Button("Show Alert2") {
            showingAlert2 = true
        }
        .alert("Important message", isPresented: $showingAlert2) {
            Button("OK", role: .cancel) { }
        } message: {
            Text("Please read this.")
        }
        
    }
}

#Preview {
    testView()
}
