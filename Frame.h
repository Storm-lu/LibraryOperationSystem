#pragma once

#include "Reader.h"
#include "Record.h"
#include "Statistics.h"
#include "books/Book.h"

#include <string>
#include <vector>

using namespace std;

class Frame
{
public:
	int run();

private:
    string makeDate(int offsetDays = 0);
    bool readUnsigned(const string& prompt, unsigned int& value);
    void clearScreen();
    void waitForEnter(const string& message = "Press Enter to continue...");
    bool parseUnsigned(const string& text, unsigned int& value);
    bool loadReaders(vector<Reader>& readers);
    bool saveReaders(const vector<Reader>& readers);
    void registerReader(vector<Reader>& readers);
    Book* findBook(vector<Book>& books, unsigned int bookId);
    const Book* findBook(const vector<Book>& books, unsigned int bookId);
    Reader* findReader(vector<Reader>& readers, unsigned int readerId);
    bool loadRecords(vector<Record>& records);
    bool saveRecords(const vector<Record>& records);
    bool loadInventory(vector<Book>& books);
    bool saveInventory(const vector<Book>& books);
    bool saveLibraryData(const vector<Book>& books, const vector<Record>& records);
    bool restoreActiveLoans(vector<Book>& books, vector<Reader>& readers, const vector<Record>& records);
    void showBooks(const vector<Book>& books);
    void showBookDetails(const Book& book, const vector<Reader>& readers, const vector<Record>& records);
    void showBookCatalogPage(const vector<Book>& books, const vector<Reader>& readers, const vector<Record>& records);
    void searchBooks(const vector<Book>& books);
    void borrowBook(vector<Book>& books, Reader& reader, vector<Record>& records, Statistics& statistics);
    void returnBook(vector<Book>& books, Reader& reader, vector<Record>& records, Statistics& statistics);
    void showMyRecords(const vector<Book>& books, const Reader& reader, const vector<Record>& records);
};



/*
Frame 是图书馆系统的交互控制类：负责启动和保存系统、处理读者输入、调用借阅/归还逻辑，并显示图书和借阅信息。除公开的 run() 外，Frame.h 中其余成员函数都是私有辅助函数。
输入、日期与界面辅助
•	makeDate(int offsetDays)：取得本地日期，按天数偏移后返回 YYYY-MM-DD 字符串。借阅时用它生成借阅日期和默认 30 天后的到期日期。
•	parseUnsigned(const string&, unsigned int&)：去除首尾空白后，将只含数字的文本解析为无符号整数；拒绝空文本、非数字和超出 unsigned int 范围的值。
•	readUnsigned(const string&, unsigned int&)：显示提示并循环读取整数，直到输入有效；若输入流结束则返回 false。
•	clearScreen()：根据操作系统执行清屏命令。
•	waitForEnter(const string&)：显示提示并等待读者按回车继续。
读者与图书查找
•	loadReaders(vector<Reader>&)：从 users.txt 读取读者，逐行校验数据，跳过格式错误、无效或重复 ID 的记录；返回是否成功读入至少一名读者。
•	saveReaders(const vector<Reader>&)：将读者写入 users.txt，每行格式为 读者ID|姓名|借阅上限。
•	registerReader(vector<Reader>&)：交互式注册读者，默认建议使用下一个 ID，并允许输入姓名和借阅上限；验证通过后添加到列表并尝试保存。
•	findBook(vector<Book>&, unsigned int)：按 ID 查找图书并返回可修改的指针；找不到时返回 nullptr。
•	findBook(const vector<Book>&, unsigned int)：只读版本，按 ID 查找图书，返回指向常量图书的指针。
•	findReader(vector<Reader>&, unsigned int)：按 ID 查找读者并返回可修改的指针；找不到时返回 nullptr。
借阅记录与库存文件
•	loadRecords(vector<Record>&)：从 records.txt 读取借阅记录，校验字段和数字格式，跳过无效行；返回是否读入至少一条记录。
•	saveRecords(const vector<Record>&)：将借阅记录写入 records.txt，包含记录 ID、读者 ID、图书 ID、借阅日期、到期日期和是否归还。
•	loadInventory(vector<Book>&)：从 inventory.txt 读取图书 ID、总册数和可借册数；通过图书 ID 创建对应图书对象，限制可借册数不超过总册数，并跳过无效或重复记录。
•	saveInventory(const vector<Book>&)：将库存写入 inventory.txt，每行保存图书 ID、总册数和可借册数。
•	saveLibraryData(const vector<Book>&, const vector<Record>&)：同时保存库存与借阅记录，只有两项都成功时才返回 true。
•	restoreActiveLoans(vector<Book>&, vector<Reader>&, const vector<Record>&)：根据未归还记录恢复读者当前借阅列表，并重新计算每本书的可借册数。若记录引用了不存在的读者或图书，或恢复读者借阅时发生异常，会标记数据不一致并返回 false。
图书展示与搜索
•	showBooks(const vector<Book>&)：打印完整图书目录及册数信息。
•	showBookDetails(const Book&, const vector<Reader>&, const vector<Record>&)：显示指定图书详情、当前借阅者和历史记录，并根据日期标注逾期状态。
•	showBookCatalogPage(const vector<Book>&, const vector<Reader>&, const vector<Record>&)：分页展示目录，支持翻页、输入图书 ID 查看详情，以及返回菜单。
•	searchBooks(const vector<Book>&)：按图书 ID、书名或作者搜索；书名和作者的匹配不区分大小写。
借阅与归还
•	borrowBook(vector<Book>&, Reader&, vector<Record>&, Statistics&)：展示目录并读取图书 ID；检查图书是否存在、有无库存、读者是否已借该书以及是否达到借阅上限。借阅成功后更新图书、读者、记录和统计信息，并尝试保存数据。
•	returnBook(vector<Book>&, Reader&, vector<Record>&, Statistics&)：列出当前读者未归还的图书，确认所选图书确实由该读者借出后，标记记录已归还、更新库存和读者状态，并尝试保存数据；若逾期会提示。
•	showMyRecords(const vector<Book>&, const Reader&, const vector<Record>&)：显示当前读者的借阅上限、未归还图书（含逾期提示）以及完整借阅历史。
主流程
•	run()：程序入口。加载库存、读者和借阅记录；必要时创建默认图书目录和演示读者，并恢复未归还借阅。随后负责读者登录、注册、切换以及菜单分发，最后保存数据并退出。菜单中的统计选项会显示图书馆统计和本次运行期间的统计。
另外，Frame.cpp 匿名命名空间中的辅助函数负责默认数据创建、图书 ID 到具体图书类的映射、借阅记录 ID 生成、逾期判断，以及图书表格的格式化输出。
*/

