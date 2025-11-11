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

        // 6. Protocol Examples
        .executable(name: "protocol_syntax", targets: ["protocol_syntax"]),
        .executable(name: "protocols_as_types", targets: ["protocols_as_types"]),
        .executable(name: "protocol_extensions", targets: ["protocol_extensions"]),

        // 7. Closures Examples
        .executable(name: "closure_syntax", targets: ["closure_syntax"]),
        .executable(name: "closures_in_api", targets: ["closures_in_api"]),
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

        // --- 6. Protocol Examples ---
        .executableTarget(
            name: "protocol_syntax",
            path: "6.protocol",
            sources: ["1_protocol_syntax.swift"]
        ),
        .executableTarget(
            name: "protocols_as_types",
            path: "6.protocol",
            sources: ["2_protocols_as_types.swift"]
        ),
        .executableTarget(
            name: "protocol_extensions",
            path: "6.protocol",
            sources: ["3_protocol_extensions.swift"]
        ),

        // --- 7. Closures Examples ---
        .executableTarget(
            name: "closure_syntax",
            path: "7.closures",
            sources: ["1_closure_syntax.swift"]
        ),
        .executableTarget(
            name: "closures_in_api",
            path: "7.closures",
            sources: ["2_closures_in_api.swift"]
        ),
    ]
)
