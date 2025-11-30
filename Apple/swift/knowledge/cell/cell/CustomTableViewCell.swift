//
//  CustomTableViewCell.swift
//  cell
//
//  Cell 复用示例 - 自定义 Cell
//

import UIKit

class CustomTableViewCell: UITableViewCell {

    // 用于追踪 cell 的创建和复用
    private static var cellCount = 0
    private let cellId: Int

    // MARK: - UI 组件
    private let titleLabel: UILabel = {
        let label = UILabel()
        label.font = .systemFont(ofSize: 18, weight: .bold)
        label.textColor = .label
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()

    private let detailLabel: UILabel = {
        let label = UILabel()
        label.font = .systemFont(ofSize: 14, weight: .regular)
        label.textColor = .secondaryLabel
        label.numberOfLines = 0
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()

    private let iconImageView: UIImageView = {
        let imageView = UIImageView()
        imageView.contentMode = .scaleAspectFill
        imageView.clipsToBounds = true
        imageView.layer.cornerRadius = 20
        imageView.backgroundColor = .systemGray5
        imageView.translatesAutoresizingMaskIntoConstraints = false
        return imageView
    }()

    // MARK: - 初始化
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        CustomTableViewCell.cellCount += 1
        self.cellId = CustomTableViewCell.cellCount
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        setupUI()
        print("🆕 创建新 Cell #\(cellId) (总共创建了 \(CustomTableViewCell.cellCount) 个 cell)")
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    // MARK: - UI 设置
    private func setupUI() {
        contentView.addSubview(iconImageView)
        contentView.addSubview(titleLabel)
        contentView.addSubview(detailLabel)

        NSLayoutConstraint.activate([
            // 图标
            iconImageView.leadingAnchor.constraint(
                equalTo: contentView.leadingAnchor, constant: 16),
            iconImageView.centerYAnchor.constraint(equalTo: contentView.centerYAnchor),
            iconImageView.widthAnchor.constraint(equalToConstant: 40),
            iconImageView.heightAnchor.constraint(equalToConstant: 40),

            // 标题
            titleLabel.leadingAnchor.constraint(
                equalTo: iconImageView.trailingAnchor, constant: 12),
            titleLabel.trailingAnchor.constraint(
                equalTo: contentView.trailingAnchor, constant: -16),
            titleLabel.topAnchor.constraint(equalTo: contentView.topAnchor, constant: 12),

            // 详情
            detailLabel.leadingAnchor.constraint(equalTo: titleLabel.leadingAnchor),
            detailLabel.trailingAnchor.constraint(equalTo: titleLabel.trailingAnchor),
            detailLabel.topAnchor.constraint(equalTo: titleLabel.bottomAnchor, constant: 4),
            detailLabel.bottomAnchor.constraint(equalTo: contentView.bottomAnchor, constant: -12),
        ])
    }

    // MARK: - 配置 Cell
    func configure(title: String, detail: String, iconName: String) {
        titleLabel.text = title
        detailLabel.text = detail

        // 使用系统图标
        if let image = UIImage(systemName: iconName) {
            iconImageView.image = image
            iconImageView.tintColor = .systemBlue
        }
    }

    // MARK: - 复用准备
    override func prepareForReuse() {
        super.prepareForReuse()

        // 🔑 关键：重置 cell 状态，避免显示旧数据
        titleLabel.text = nil
        detailLabel.text = nil
        iconImageView.image = nil

        print("🔄 Cell #\(cellId) 被复用，已重置状态")
    }
}
