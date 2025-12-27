基于C++的完整命令行的个人记账系统
## 功能
### 用户管理
- **用户注册**：创建个人账户，自动生成唯一用户ID
- **用户登录**：安全的用户名密码验证系统
- **数据隔离**：每个用户的交易记录独立存储
### 交易管理
- **记录收支**：支持"收入"和"支出"两种类型
- **分类管理**：可自定义交易类别（餐饮、购物、工资等）
- **详细记录**：金额、类型、类别、日期、备注完整记录
- **数据验证**：金额正数验证、日期格式校验、输入合法性的检查
### 统计分析
- **余额计算**：自动计算当前总余额
- **支出分类统计**：按类别统计支出总额和交易次数
- **交易查询**：查看所有交易记录，表格化显示
### 环境要求
- **编译器**：支持C++11标准
- **开发环境**：Visual Studio 2019+ 或 g++/clang++
- **Windows特定**：需要使用Windows API解决中文显示问题
### 编译方法
#### 方法一：使用Visual Studio（推荐）
1. 双击打开 `AccountBook.sln` 文件
2. 选择 `Debug` 或 `Release` 模式
3. 按 `F5` 编译并运行
#### 方法二：命令行编译（Windows）
# 使用Visual Studio命令行工具
cl AccountBook.cpp /EHsc /std:c++11
# 或使用MinGW
g++ AccountBook.cpp -o AccountBook.exe -std=c++11
## 项目结构
AccountBook/
├── AccountBook.cpp              # 主程序源代码
├── AccountBook.sln              # Visual Studio解决方案文件
├── AccountBook.vcxproj          # Visual Studio项目文件
├── AccountBook.vcxproj.filters  # VS项目过滤器文件
├── README.md                    # 项目说明文档
├── .gitignore                   # Git忽略规则
├── users.csv                    # 用户数据文件（自动生成）
└── transactions_[user_id].csv   # 用户交易记录文件（自动生成）
## 核心技术
### 数据结构
- **Transaction结构体**：存储单笔交易的完整信息
- **User结构体**：存储用户信息和其交易记录
- **STL容器**：使用`vector`存储用户列表，`map`进行类别统计
### 关键功能
1. **输入验证系统**：
    - 日期格式验证（YYYY-MM-DD）
    - 金额有效性检查
    - 类型合法性验证
    - 防止空输入和非法字符
2. **文件管理**：
    - 自动创建数据文件
    - CSV格式读写
    - 异常处理和错误提示
3. **用户界面**：
    - 分层菜单系统
    - 表格化数据显示
    - 中文支持（Windows系统）
## 已知问题和解决方案
### 中文编码问题
- **问题**：在非Windows系统或某些终端中可能出现中文乱码
- **解决方案**：代码中已使用Windows API设置控制台编码，其他系统需要相应调整