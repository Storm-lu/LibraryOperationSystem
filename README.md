# LibraryOperationSystem

一个基于 C++20 的命令行图书管理系统，也是面向对象程序设计课程的练习项目。

程序用 `Frame` 类驱动一套完整的菜单式交互：读者可以浏览/搜索藏书、借书、还书、查看自己的借阅记录；
管理员可以查看全部借阅统计，并按累计借阅次数评选出前三名「图书馆之星」。
所有状态保存在三个纯文本文件中，程序退出时自动落盘，下次启动时原样恢复。

## 功能特性

- **读者登录**：按读者 ID 登录，ID 不存在时可现场注册新读者，随时可切换读者。
- **图书目录**：分页浏览（每页 10 本），支持 `n` / `p` 翻页、输入书号查看详情。
- **图书搜索**：按书名、作者模糊匹配，或直接输入书号精确查找。
- **借阅**：校验库存、借阅上限、同一本书是否已有未还记录，成功后扣减可借数并写入借阅记录。
- **归还**：列出当前在借书目，按书号归还，回补可借数并把记录标记为已归还。
- **我的记录**：显示当前在借（含应还日期、是否逾期）与全部历史借阅记录。
- **统计分析**：逐本统计借阅次数、逐位读者统计当前借阅/上限/累计借阅，并输出累计借阅最多的前三名读者。
- **持久化**：`inventory.txt` / `users.txt` / `records.txt` 三个数据文件，启动时载入、退出时保存；
  数据文件缺失时会自动生成一套演示数据（10 位读者 + 30 种图书），因此程序可以冷启动。

### 业务校验（边界情况均有明确提示）

| 场景 | 处理方式 |
| --- | --- |
| 图书 ID 不存在 | 提示 `no book with ID xxx exists in the catalogue` |
| 某本书可借数为 0 | 提示 `every copy of "..." is already on loan` |
| 同一本书已有未还记录 | 提示 `you have not returned your copy of "..." yet` |
| 达到借阅上限 | 提示 `you have reached your borrowing limit of N books` |
| 归还未借阅的图书 | 提示 `you have not borrowed "...", so it cannot be returned` |
| 读者 ID 不存在 | 提示并询问是否现场注册 |
| 输入非数字 / 负数 | 提示 `please enter a non-negative whole number` 并重试 |

## 环境要求

- Windows 10 / 11
- Visual Studio 2022（使用 `v145` 平台工具集、Windows SDK 10.0）
- C++20（项目已启用 `/std:c++20`、`/utf-8`、SDL 检查）

## 编译与运行

**方式一：Visual Studio**

打开 `LibraryOperationSystem.slnx`，选择 `Debug | x64` 或 `Release | x64`，按 `F5` 运行。

**方式二：命令行（MSBuild）**

```bat
msbuild LibraryOperationSystem.slnx /p:Configuration=Release /p:Platform=x64
x64\Release\LibraryOperationSystem.exe
```

> 程序按**相对路径**读取数据文件，请把工作目录设为项目根目录（直接在 VS 里运行会自动满足）。

## 目录结构

```
LibraryOperationSystem\
├─ main.cpp                     程序入口，构造 Frame 并调用 run()
├─ Frame.h / Frame.cpp          主控制器：界面、菜单流程、文件读写、业务校验
├─ books\                       图书类层次
│  ├─ Book.h / Book.cpp         抽象出的图书基类（书号、书名、作者、总数、可借数）
│  └─ *.h / *.cpp               30 个具体书目派生类（AliceInWonderland … WutheringHeights）
├─ Reader.h / Reader.cpp        读者类（ID、姓名、借阅上限、在借书单）
├─ Record.h / Record.cpp        借阅记录类（记录号、读者、图书、借出日、应还日、是否归还）
├─ Statistics.h / Statistics.cpp 统计与排行榜
├─ inventory.txt                馆藏：书号 | 总数 | 可借数
├─ users.txt                    读者：ID | 姓名 | 借阅上限
├─ records.txt                  借阅记录：记录号 | 读者ID | 书号 | 借出日 | 应还日 | 是否归还
└─ .github\copilot-instructions.md  代码风格约定
```

## 数据文件格式

均为以 `|` 分隔的纯文本，每行一条，UTF-8 编码。

**inventory.txt** — 馆藏与库存

```
书号|总册数|可借册数
1|3|2
2|2|1
```

**users.txt** — 读者信息

```
读者ID|姓名|借阅上限
1|StormLowe|3
2|ZhanSan|3
```

**records.txt** — 借阅记录（`0` = 未归还，`1` = 已归还）

```
记录号|读者ID|书号|借出日期|应还日期|是否归还
1|1|1|2026-11-24|2026-12-24|0
3|2|3|2026-11-24|2026-12-24|1
```

启动时程序会依据未归还记录重建每位读者的在借清单，并按 `总册数 - 未归还记录数` 校准可借册数，
因此手工编辑数据文件后也能保持一致；格式错误（缺字段、非数字、重复 ID）的行会被跳过而不会导致崩溃。

## 主要参数

| 参数 | 取值 | 位置 |
| --- | --- | --- |
| 演示图书种类 | 30 | `Frame.cpp` 的 `DEFAULT_BOOK_COUNT` |
| 演示读者数量 | 10 | `Frame.cpp` 的 `DEFAULT_READER_COUNT` |
| 每本书默认册数 | 2 | `DEFAULT_BOOK_COPIES` |
| 单读者借阅上限 | 3 | `DEFAULT_MAX_BORROW_LIMIT` |
| 借期（天） | 30 | `DEFAULT_LOAN_DAYS` |
| 目录分页大小 | 10 | `CATALOG_PAGE_SIZE` |

## 设计说明

- 30 个具体书目类继承自 `Book`，各自在构造函数中提供书名、作者及专属的版本信息；
  容器统一使用 `vector<Book>` 值语义保存，`Frame` 只依赖 `Book` 基类接口。
- 派生类中的 `getDetail()` / `getSummary()` 目前不是虚函数，在值语义容器中会被切片，
  因此界面只展示基类字段。若需要在详情页显示各书目的简介，需要将其改为 `virtual`
  并把容器换成 `vector<unique_ptr<Book>>`。
- `Statistics` 与 `Reader` / `Book` 之间为友元关系，避免为统计功能额外暴露接口。