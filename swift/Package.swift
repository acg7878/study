// swift-tools-version: 6.2
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "swift-study-examples",
    products: [
        // 1. Data Type Examples
        .executable(name: "let_var", targets: ["let_var"]),
        .executable(name: "tuple_example", targets: ["tuple_example"]),
        .executable(name: "array_init_example", targets: ["array_init_example"]),

        // 2. Control Flow Examples
        .executable(name: "if_else", targets: ["if_else"]),
        .executable(name: "switch_example", targets: ["switch_example"]),
        .executable(name: "loops", targets: ["loops"]),
        .executable(name: "control_transfer", targets: ["control_transfer"]),
        .executable(name: "guard_example", targets: ["guard_example"]),
    ],
    targets: [
        // --- 1. Data Type Examples ---
        .executableTarget(
            name: "let_var",
            path: "1.data_type",
            sources: ["let_var.swift"]
        ),
        .executableTarget(
            name: "tuple_example",
            path: "1.data_type/Collection",
            sources: ["tuple.swift"]
        ),
        .executableTarget(
            name: "array_init_example",
            path: "1.data_type/Collection/Array",
            sources: ["init.swift"]
        ),
        
        // --- 2. Control Flow Examples ---
        .executableTarget(
            name: "if_else",
            path: "2.control_flow",
            sources: ["1_if_else.swift"]
        ),
        .executableTarget(
            name: "switch_example",
            path: "2.control_flow",
            sources: ["2_switch.swift"]
        ),
        .executableTarget(
            name: "loops",
            path: "2.control_flow",
            sources: ["3_loops.swift"]
        ),
        .executableTarget(
            name: "control_transfer",
            path: "2.control_flow",
            sources: ["4_control_transfer.swift"]
        ),
        .executableTarget(
            name: "guard_example",
            path: "2.control_flow",
            sources: ["5_guard.swift"]
        ),
    ]
)
