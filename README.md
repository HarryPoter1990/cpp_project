# cpp_project
AccountBook
个人记账管理系统 (AccountBook)
一个基于C++的完整命令行个人记账系统，支持多用户管理、交易记录、分类统计和数据持久化存储。

✨ 功能特性
🏦 用户管理
用户注册：创建个人账户，自动生成唯一用户ID

用户登录：安全的用户名密码验证系统

数据隔离：每个用户的交易记录独立存储

💰 交易管理
记录收支：支持"收入"和"支出"两种类型

分类管理：可自定义交易类别（餐饮、购物、工资等）

详细记录：金额、类型、类别、日期、备注完整记录

数据验证：金额正数验证、日期格式校验、输入合法性检查

📊 统计分析
余额计算：自动计算当前总余额

支出分类统计：按类别统计支出总额和交易次数

交易查询：查看所有交易记录，表格化显示

💾 数据持久化
CSV格式存储：用户数据和交易记录分别存储

自动加载：启动时自动加载已有数据

实时保存：每次操作后自动保存，防止数据丢失

文件分离：每个用户拥有独立的交易文件

🚀 快速开始
环境要求
操作系统：Windows（推荐）/ Linux / macOS

编译器：支持C++11标准

开发环境：Visual Studio 2019+ 或 g++/clang++

Windows特定：需要使用Windows API解决中文显示问题

编译方法
方法一：使用Visual Studio（推荐）
双击打开 AccountBook.sln 文件

选择 Debug 或 Release 模式

按 F5 编译并运行

方法二：命令行编译（Windows）
bash
# 使用Visual Studio命令行工具
cl AccountBook.cpp /EHsc /std:c++11

# 或使用MinGW
g++ AccountBook.cpp -o AccountBook.exe -std=c++11
方法三：Linux/macOS
bash
g++ AccountBook.cpp -o AccountBook -std=c++11
./AccountBook
运行程序
程序运行后会出现主菜单：

text
=== 个人记账系统 ===
1. 注册新用户
2. 用户登录
3. 退出系统
请选择操作 (1-3):
📁 项目结构
text
AccountBook/
├── AccountBook.cpp              # 主程序源代码
├── AccountBook.sln              # Visual Studio解决方案文件
├── AccountBook.vcxproj          # Visual Studio项目文件
├── AccountBook.vcxproj.filters  # VS项目过滤器文件
├── README.md                    # 项目说明文档
├── .gitignore                   # Git忽略规则
├── users.csv                    # 用户数据文件（自动生成）
└── transactions_[user_id].csv   # 用户交易记录文件（自动生成）
🔧 核心技术
数据结构
Transaction结构体：存储单笔交易的完整信息

User结构体：存储用户信息和其交易记录

STL容器：使用vector存储用户列表，map进行类别统计

关键功能
输入验证系统：

日期格式验证（YYYY-MM-DD）

金额有效性检查

类型合法性验证

防止空输入和非法字符

文件管理：

自动创建数据文件

CSV格式读写

异常处理和错误提示

用户界面：

分层菜单系统

表格化数据显示

中文支持（Windows系统）

代码亮点
面向对象设计：使用结构体封装相关数据

异常处理：全面的输入验证和错误处理

模块化函数：每个功能独立封装，便于维护

内存管理：使用智能指针避免内存泄漏

使用示例
1. 注册用户
text
=== 用户注册 ===
请输入用户名: 张三
请输入密码: 123456
注册成功! 用户ID: 1703689200_1234
2. 添加交易记录
text
=== 添加新记录 ===
请输入金额: 150.50
请输入类型 (收入/支出): 支出
请输入类别 (例如: 餐饮, 购物, 工资): 餐饮
请输入日期 (格式: YYYY-MM-DD): 2024-01-15
请输入备注: 午餐
交易记录添加成功!
3. 查看统计
text
=== 账户统计 ===
总余额: 2350.75 元

=== 按类别统计支出 ===
类别             总金额       记录数
---------------------------------------------
餐饮            850.50         3
购物            1200.00        2
交通            300.25         4
⚙️ 配置文件
数据文件格式
users.csv
text
user_id,username,password
1703689200_1234,张三,123456
1703689300_5678,李四,abcdef
transactions_[user_id].csv
text
金额,类型,类别,日期,备注
150.50,支出,餐饮,2024-01-15,午餐
3000.00,收入,工资,2024-01-10,一月工资
🐛 已知问题和解决方案
1. 中文编码问题
问题：在非Windows系统或某些终端中可能出现中文乱码

解决方案：代码中已使用Windows API设置控制台编码，其他系统需要相应调整

2. 文件路径问题
问题：文件保存在程序所在目录

注意：确保程序有当前目录的读写权限

3. 数据安全
注意：密码以明文存储，不适合生产环境

建议：未来可添加密码加密功能

🔮 未来改进计划
添加数据加密功能

支持图形用户界面（GUI）

增加数据备份和恢复功能

添加数据可视化图表

支持导出Excel/PDF报表

添加预算管理功能

支持多币种和汇率转换

👥 贡献指南
欢迎提交Issue和Pull Request！贡献步骤：

Fork本仓库

创建功能分支 (git checkout -b feature/AmazingFeature)

提交更改 (git commit -m 'Add some AmazingFeature')

推送到分支 (git push origin feature/AmazingFeature)

打开Pull Request

📄 许可证
本项目基于MIT许可证开源 - 查看 LICENSE 文件了解详情