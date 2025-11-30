# Cell 复用示例

这个项目演示了 UITableView 中 Cell 复用的机制和实现方法。

## 📚 核心概念

### 什么是 Cell 复用？

Cell 复用是 UITableView 和 UICollectionView 的性能优化机制：
- **不创建无限个 cell**：即使有 1000 行数据，也只会创建屏幕可见的 cell（约 10-15 个）
- **重复使用已创建的 cell**：当 cell 滚动出屏幕时，放入复用池；需要新 cell 时，从复用池取出
- **减少内存占用**：从 1000 个 cell 对象减少到 ~15 个
- **提升滚动性能**：避免频繁创建和销毁对象

## 🔑 关键步骤

### 1. 注册 Cell

```swift
tableView.register(CustomTableViewCell.self, 
                  forCellReuseIdentifier: "CustomCell")
```

告诉 tableView 使用哪种 cell 和复用标识符。

### 2. 从复用池获取 Cell

```swift
let cell = tableView.dequeueReusableCell(withIdentifier: "CustomCell", 
                                        for: indexPath) as! CustomTableViewCell
```

工作原理：
- 检查复用池是否有相同 identifier 的空闲 cell
- 如果有，取出并返回（复用）
- 如果没有，创建新的 cell
- 返回 cell（可能是复用的，也可能是新创建的）

### 3. 更新 Cell 内容

```swift
// ⚠️ 重要：每次都必须更新内容，避免显示旧数据
let item = data[indexPath.row]
cell.configure(title: item.title, 
              detail: item.detail, 
              iconName: item.iconName)
```

### 4. 重置 Cell 状态（可选但推荐）

```swift
override func prepareForReuse() {
    super.prepareForReuse()
    // 重置 cell 状态，避免显示旧数据
    titleLabel.text = nil
    detailLabel.text = nil
    iconImageView.image = nil
}
```

## 📊 性能对比

### 不使用复用
- 1000 行数据 = 1000 个 cell 对象
- 内存占用：~50MB
- 滚动性能：卡顿

### 使用复用
- 1000 行数据 = ~15 个 cell 对象（屏幕可见数量）
- 内存占用：~1MB
- 滚动性能：流畅

## 🎯 运行示例

1. 运行项目
2. 观察控制台输出，查看 cell 复用情况
3. 快速滚动列表，体验流畅性能
4. 注意：即使有 1000 条数据，内存占用也很低

## ⚠️ 常见错误

### 错误 1：忘记更新内容

```swift
// ❌ 错误
let cell = tableView.dequeueReusableCell(...)
return cell  // 可能显示旧数据

// ✅ 正确
let cell = tableView.dequeueReusableCell(...)
cell.configure(...)  // 必须更新
return cell
```

### 错误 2：异步加载图片导致错位

```swift
// ❌ 错误：可能显示错误的图片
loadImage(url: url) { image in
    cell.imageView.image = image
}

// ✅ 正确：检查 URL 是否匹配
cell.currentURL = url
loadImage(url: url) { image in
    if cell.currentURL == url {
        cell.imageView.image = image
    }
}
```

## 📝 文件说明

- `CustomTableViewCell.swift`: 自定义 Cell 类
- `TableViewContainer.swift`: UITableView 容器和控制器
- `ContentView.swift`: SwiftUI 主视图

## 🔗 相关知识点

- UITableView 复用机制
- prepareForReuse() 方法
- dequeueReusableCell 方法
- 内存优化
- 滚动性能优化

