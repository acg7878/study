// swift-tools-version: 6.2
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "swift-study-examples",
    products: [
        // 1. Data Type Examples
        .executable(name: "let_var", targets: ["let_var"]),
        .executable(name: "tuple", targets: ["tuple"]),
        .executable(name: "array_init", targets: ["array_init"]),

        // 2. Control Flow Examples
        .executable(name: "if_else", targets: ["if_else"]),
        .executable(name: "switch_example", targets: ["switch_example"]),
        .executable(name: "loops", targets: ["loops"]),
        .executable(name: "control_transfer", targets: ["control_transfer"]),
        .executable(name: "guard_example", targets: ["guard_example"]),

        // 3. Function Examples
        .executable(name: "func_basics", targets: ["func_basics"]),

        // 5. Compound Type Examples
        .executable(name: "struct_class", targets: ["struct_class"]),
        .executable(name: "value_reference", targets: ["value_reference"]),
    ],
    targets: [
        // --- 1. Data Type Examples ---
        .executableTarget(
            name: "let_var",
            path: "1.data_type",
            sources: ["let_var.swift"]
        ),
        .executableTarget(
            name: "tuple",
            path: "1.data_type/Collection",
            sources: ["tuple.swift"]
        ),
        .executableTarget(
            name: "array_init",
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

        // --- 3. Function Examples ---
        .executableTarget(
            name: "func_basics",
            path: "3.function",
            sources: ["1_func_basics.swift"]
        ),
        
        // --- 5. Compound Type Examples ---
        .executableTarget(
            name: "struct_class",
            path: "5.compound_type",
            sources: ["1_struct_class.swift"]
        ),
        .executableTarget(
            name: "value_reference",
            path: "5.compound_type",
            sources: ["2_value_reference.swift"]
        ),
    ]
)
