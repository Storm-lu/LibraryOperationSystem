#include "Frame.h"

#include "books/AliceInWonderland.h"
#include "books/BraveNewWorld.h"
#include "books/CatcherInTheRye.h"
#include "books/CrimeAndPunishment.h"
#include "books/DonQuixote.h"
#include "books/Dracula.h"
#include "books/DreamOfTheRedChamber.h"
#include "books/Frankenstein.h"
#include "books/HarryPotterAndThePhilosophersStone.h"
#include "books/JaneEyre.h"
#include "books/JourneyToTheWest.h"
#include "books/LesMiserables.h"
#include "books/MobyDick.h"
#include "books/NineteenEightyFour.h"
#include "books/OneHundredYearsOfSolitude.h"
#include "books/PrideAndPrejudice.h"
#include "books/SherlockHolmes.h"
#include "books/TheAlchemist.h"
#include "books/TheCountOfMonteCristo.h"
#include "books/TheGreatGatsby.h"
#include "books/TheHobbit.h"
#include "books/TheLittlePrince.h"
#include "books/TheLordOfTheRings.h"
#include "books/TheMoonAndSixpence.h"
#include "books/TheOldManAndTheSea.h"
#include "books/TheStranger.h"
#include "books/TheTrial.h"
#include "books/ToKillAMockingbird.h"
#include "books/WarAndPeace.h"
#include "books/WutheringHeights.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


/*
程序启动后，先从文件加载图书库存、读者和借阅记录；如果库存或读者数据不存在，就创建默认数据。接着根据未归还记录恢复读者的借阅状态，并重新计算每本书的可借数量。
进入登录界面后，读者输入 ID 登录；若 ID 不存在，可选择注册。登录成功后进入功能菜单，可浏览或搜索图书、借书、还书、查看个人借阅记录、查看统计、注册读者或切换账号。
借书时，系统检查图书是否存在且有库存，并确认读者未重复借阅、未超过借阅上限。检查通过后，更新库存、读者借阅状态、借阅记录和统计数据，并保存库存与记录。还书时，系统确认该书确实由当前读者借出，然后标记记录已归还、更新库存、读者状态和统计数据，并保存数据。
读者选择退出后，系统保存读者、库存和借阅记录，显示保存结果并结束程序。
*/


// 匿名命名空间用于封装内部实现细节，避免与其他文件中的符号冲突
namespace
{
	const char* const INVENTORY_FILE = "inventory.txt";
	const char* const READERS_FILE = "users.txt";
	const char* const RECORDS_FILE = "records.txt";

	const unsigned int DEFAULT_BOOK_COUNT = 30;
	const unsigned int DEFAULT_READER_COUNT = 10;
	const unsigned int DEFAULT_BOOK_COPIES = 2;
	const unsigned int DEFAULT_MAX_BORROW_LIMIT = 3;
	const int DEFAULT_LOAN_DAYS = 30;
	const size_t CATALOG_PAGE_SIZE = 10;
	const int ID_COLUMN = 6;
	const int TITLE_COLUMN = 44;
	const int AUTHOR_COLUMN = 28;

	string trim(const string& text)
	{
		size_t first = 0;
		while (first < text.size() && isspace(static_cast<unsigned char>(text[first])) != 0)
		{
			++first;
		}
		size_t last = text.size();
		while (last > first && isspace(static_cast<unsigned char>(text[last - 1])) != 0)
		{
			--last;
		}
		return text.substr(first, last - first);
	}

	string toLowerText(const string& text)
	{
		string result = text;
		for (char& character : result)
		{
			character = static_cast<char>(tolower(static_cast<unsigned char>(character)));
		}
		return result;
	}

	// 每本书的编号固定对应 books 目录下的一个派生类，书名与作者只在那里维护一份。
	Book createBook(unsigned int bookId, unsigned int totalCopies)
	{
		switch (bookId)
		{
		case 1: return AliceInWonderland(bookId, totalCopies);
		case 2: return BraveNewWorld(bookId, totalCopies);
		case 3: return CatcherInTheRye(bookId, totalCopies);
		case 4: return CrimeAndPunishment(bookId, totalCopies);
		case 5: return DonQuixote(bookId, totalCopies);
		case 6: return Dracula(bookId, totalCopies);
		case 7: return DreamOfTheRedChamber(bookId, totalCopies);
		case 8: return Frankenstein(bookId, totalCopies);
		case 9: return HarryPotterAndThePhilosophersStone(bookId, totalCopies);
		case 10: return JaneEyre(bookId, totalCopies);
		case 11: return JourneyToTheWest(bookId, totalCopies);
		case 12: return LesMiserables(bookId, totalCopies);
		case 13: return MobyDick(bookId, totalCopies);
		case 14: return NineteenEightyFour(bookId, totalCopies);
		case 15: return OneHundredYearsOfSolitude(bookId, totalCopies);
		case 16: return PrideAndPrejudice(bookId, totalCopies);
		case 17: return SherlockHolmes(bookId, totalCopies);
		case 18: return TheAlchemist(bookId, totalCopies);
		case 19: return TheCountOfMonteCristo(bookId, totalCopies);
		case 20: return TheGreatGatsby(bookId, totalCopies);
		case 21: return TheHobbit(bookId, totalCopies);
		case 22: return TheLittlePrince(bookId, totalCopies);
		case 23: return TheLordOfTheRings(bookId, totalCopies);
		case 24: return TheMoonAndSixpence(bookId, totalCopies);
		case 25: return TheOldManAndTheSea(bookId, totalCopies);
		case 26: return TheStranger(bookId, totalCopies);
		case 27: return TheTrial(bookId, totalCopies);
		case 28: return ToKillAMockingbird(bookId, totalCopies);
		case 29: return WarAndPeace(bookId, totalCopies);
		case 30: return WutheringHeights(bookId, totalCopies);
		default: return Book(bookId, "Unknown Title", "Unknown Author", totalCopies);
		}
	}

	void buildDefaultInventory(vector<Book>& books)
	{
		for (unsigned int bookId = 1; bookId <= DEFAULT_BOOK_COUNT; ++bookId)
		{
			books.push_back(createBook(bookId, DEFAULT_BOOK_COPIES));
		}
	}

	void buildDefaultReaders(vector<Reader>& readers)
	{
		const char* const names[DEFAULT_READER_COUNT] =
		{
			"StormLowe", "ZhanSan", "LiSi", "WangWu", "ZhaoLiu",
			"SunQi", "ZhouBa", "WuJiu", "ZhengShi", "ChenYi"
		};
		for (unsigned int index = 0; index < DEFAULT_READER_COUNT; ++index)
		{
			readers.emplace_back(index + 1, names[index], DEFAULT_MAX_BORROW_LIMIT);
		}
	}

	unsigned int nextRecordId(const vector<Record>& records)//返回下一个可用的借阅记录ID
	{
		unsigned int nextId = 1;
		for (const Record& record : records)//如果当前记录的ID大于等于nextId，则将nextId更新为当前记录ID加1
		{
			if (record.getRecordId() >= nextId)
			{
				nextId = record.getRecordId() + 1;
			}
		}
		return nextId;
	}

	bool isOverdue(const string& dueDate, const string& today)
	{
		return today > dueDate;
	}

	void printBookTableHeader()
	{
		cout << left << setw(ID_COLUMN) << "ID"
			<< setw(TITLE_COLUMN) << "Title"
			<< setw(AUTHOR_COLUMN) << "Author"
			<< right << setw(8) << "Copies"
			<< setw(11) << "On shelf" << '\n';
		cout << string(ID_COLUMN + TITLE_COLUMN + AUTHOR_COLUMN + 19, '-') << '\n';
	}

	void printBookRow(const Book& book)
	{
		cout << left << setw(ID_COLUMN) << book.getBookId()
			<< setw(TITLE_COLUMN) << book.getBookName()
			<< setw(AUTHOR_COLUMN) << book.getAuthor()
			<< right << setw(8) << book.getTotalCopies()
			<< setw(11) << book.getAvailableCopies() << '\n';
	}
}

string Frame::makeDate(int offsetDays)	//返回当前日期加上偏移天数后的日期字符串
{
	const time_t now = time(nullptr);	//获取当前时间的时间戳
	tm localTime = {};	//将时间戳转换为本地时间结构体
#ifdef _WIN32
	localtime_s(&localTime, &now);
#else
	localTime = *localtime(&now);
#endif
	localTime.tm_mday += offsetDays;	//将本地时间的天数加上偏移天数
	localTime.tm_isdst = -1;

	const time_t shifted = mktime(&localTime);	//将修改后的本地时间结构体转换为时间戳
	tm result = {};
#ifdef _WIN32
	localtime_s(&result, &shifted);	//将时间戳转换为本地时间结构体
#else
	result = *localtime(&shifted);
#endif
	char buffer[11] = {};
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", &result);	//将本地时间结构体格式化为YYYY-MM-DD字符串
	return buffer;	
}

bool Frame::readUnsigned(const string& prompt, unsigned int& value)
{
	string line;
	for (;;)
	{
		cout << prompt;
		if (!getline(cin, line))
		{
			cout << '\n';
			return false;
		}
		if (parseUnsigned(line, value))
		{
			return true;
		}
		cout << "Invalid input: please enter a non-negative whole number.\n";
	}
}

void Frame::clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void Frame::waitForEnter(const string& message)
{
	cout << message;
	string ignored;
	getline(cin, ignored);
}

bool Frame::parseUnsigned(const string& text, unsigned int& value)
{
	const string cleaned = trim(text);	// 去除首尾空白字符
	if (cleaned.empty())
	{
		return false;
	}
	unsigned long long result = 0;
	for (const char character : cleaned)	// 遍历每个字符
	{
		if (character < '0' || character > '9')
		{
			return false;
		}
		result = result * 10ULL + static_cast<unsigned long long>(character - '0');	// 将字符转换为数字并累加到结果中
		if (result > 0xFFFFFFFFULL)
		{
			return false;
		}
	}
	value = static_cast<unsigned int>(result);
	return true;
}

bool Frame::loadReaders(vector<Reader>& readers)
{
	readers.clear();
	ifstream input(READERS_FILE);
	if (!input.is_open())
	{
		return false;
	}

	string line;
	while (getline(input, line))
	{
		line = trim(line);
		if (line.empty())
		{
			continue;
		}
		istringstream row(line);
		string idText;
		string name;
		string limitText;
		string extra;
		unsigned int readerId = 0;
		unsigned int maxLimit = 0;
		if (!getline(row, idText, '|') || !getline(row, name, '|') || !getline(row, limitText, '|'))
		{
			continue;
		}
		if (getline(row, extra, '|'))
		{
			continue;
		}
		if (!parseUnsigned(idText, readerId) || !parseUnsigned(limitText, maxLimit))	// 解析读者ID和借阅上限
		{
			continue;
		}
		name = trim(name);
		if (readerId == 0 || name.empty() || maxLimit == 0)	// 读者ID为0、姓名为空或借阅上限为0的记录无效
		{
			continue;
		}
		if (findReader(readers, readerId) != nullptr)
		{
			continue;
		}
		readers.emplace_back(readerId, name, maxLimit);	// 将有效的读者记录添加到读者列表中
	}
	return !readers.empty();
}

bool Frame::saveReaders(const vector<Reader>& readers)
{
	ofstream output(READERS_FILE, ios::trunc);
	if (!output.is_open())
	{
		return false;
	}
	for (const Reader& reader : readers)
	{
		output << reader.getReaderId() << '|' << reader.getReaderName() << '|' << reader.getMaxBorrowLimit() << '\n';
	}
	return output.good();
}

void Frame::registerReader(vector<Reader>& readers)
{
	cout << "========== Register a New Reader ==========\n";
	unsigned int suggestedId = 1;
	for (const Reader& reader : readers)	
	{
		if (reader.getReaderId() >= suggestedId)
		{
			suggestedId = reader.getReaderId() + 1;
		}
	}

	unsigned int readerId = suggestedId;
	cout << "The next free reader ID is " << suggestedId << ".\n";
	if (!readUnsigned("Reader ID: ", readerId))
	{
		return;
	}
	if (readerId == 0)	// 读者ID为0不允许注册
	{
		cout << "Reader ID 0 is not allowed; registration cancelled.\n";
		waitForEnter();
		return;
	}
	if (findReader(readers, readerId) != nullptr)	// 读者ID已存在，不能注册
	{
		cout << "Error: reader ID " << readerId << " is already registered.\n";
		waitForEnter();
		return;
	}

	cout << "Reader name: ";
	string name;
	if (!getline(cin, name))	// 读取读者姓名
	{
		return;
	}
	name = trim(name);
	if (name.empty())
	{
		cout << "Error: the reader name cannot be empty.\n";
		waitForEnter();
		return;
	}

	cout << "Borrowing limit [" << DEFAULT_MAX_BORROW_LIMIT << "]: ";
	string limitText;
	if (!getline(cin, limitText))
	{
		return;
	}
	limitText = trim(limitText);
	unsigned int maxLimit = DEFAULT_MAX_BORROW_LIMIT;
	if (!limitText.empty())
	{
		if (!parseUnsigned(limitText, maxLimit) || maxLimit == 0)
		{
			cout << "Error: the borrowing limit must be a positive whole number.\n";
			waitForEnter();
			return;
		}
	}

	readers.emplace_back(readerId, name, maxLimit);
	if (!saveReaders(readers))
	{
		cout << "Warning: the new reader could not be written to " << READERS_FILE << ".\n";
	}
	cout << "\nReader \"" << name << "\" registered with ID " << readerId
		<< " and a borrowing limit of " << maxLimit << ".\n";
	waitForEnter();
}

Book* Frame::findBook(vector<Book>& books, unsigned int bookId)
{
	for (Book& book : books)
	{
		if (book.getBookId() == bookId)
		{
			return &book;
		}
	}
	return nullptr;
}

const Book* Frame::findBook(const vector<Book>& books, unsigned int bookId)
{
	for (const Book& book : books)
	{
		if (book.getBookId() == bookId)
		{
			return &book;
		}
	}
	return nullptr;
}

Reader* Frame::findReader(vector<Reader>& readers, unsigned int readerId)
{
	for (Reader& reader : readers)
	{
		if (reader.getReaderId() == readerId)
		{
			return &reader;
		}
	}
	return nullptr;
}

bool Frame::loadRecords(vector<Record>& records)
{
	records.clear();
	ifstream input(RECORDS_FILE);
	if (!input.is_open())
	{
		return false;
	}

	string line;
	while (getline(input, line))
	{
		line = trim(line);
		if (line.empty())
		{
			continue;
		}
		istringstream row(line);
		string recordIdText;
		string readerIdText;
		string bookIdText;
		string borrowDate;
		string returnDate;
		string returnedText;
		string extra;
		unsigned int recordId = 0;
		unsigned int readerId = 0;
		unsigned int bookId = 0;
		unsigned int returnedFlag = 0;
		if (!getline(row, recordIdText, '|') || !getline(row, readerIdText, '|') || !getline(row, bookIdText, '|')
			|| !getline(row, borrowDate, '|') || !getline(row, returnDate, '|') || !getline(row, returnedText, '|'))
		{
			continue;
		}
		if (getline(row, extra, '|'))
		{
			continue;
		}
		if (!parseUnsigned(recordIdText, recordId) || !parseUnsigned(readerIdText, readerId) || !parseUnsigned(bookIdText, bookId))
		{
			continue;
		}
		if (!parseUnsigned(returnedText, returnedFlag) || returnedFlag > 1)
		{
			continue;
		}
		if (recordId == 0 || readerId == 0 || bookId == 0)
		{
			continue;
		}
		records.emplace_back(recordId, readerId, bookId, trim(borrowDate), trim(returnDate), returnedFlag == 1);
	}
	return !records.empty();
}

bool Frame::saveRecords(const vector<Record>& records)
{
	ofstream output(RECORDS_FILE, ios::trunc);
	if (!output.is_open())
	{
		return false;
	}
	for (const Record& record : records)
	{
		output << record.getRecordId() << '|'
			<< record.getReaderId() << '|'
			<< record.getBookId() << '|'
			<< record.getBorrowDate() << '|'
			<< record.getReturnDate() << '|'
			<< (record.getIsReturned() ? 1 : 0) << '\n';
	}
	return output.good();
}

bool Frame::loadInventory(vector<Book>& books)
{
	books.clear();
	ifstream input(INVENTORY_FILE);
	if (!input.is_open())
	{
		return false;
	}

	string line;
	while (getline(input, line))
	{
		line = trim(line);
		if (line.empty())
		{
			continue;
		}
		istringstream row(line);
		string bookIdText;
		string totalText;
		string availableText;
		string extra;
		unsigned int bookId = 0;
		unsigned int totalCopies = 0;
		unsigned int availableCopies = 0;
		if (!getline(row, bookIdText, '|') || !getline(row, totalText, '|') || !getline(row, availableText, '|'))
		{
			continue;
		}
		if (getline(row, extra, '|'))
		{
			continue;
		}
		if (!parseUnsigned(bookIdText, bookId) || !parseUnsigned(totalText, totalCopies) || !parseUnsigned(availableText, availableCopies))
		{
			continue;
		}
		if (bookId == 0 || totalCopies == 0)
		{
			continue;
		}
		if (availableCopies > totalCopies)
		{
			availableCopies = totalCopies;
		}
		if (findBook(books, bookId) != nullptr)
		{
			continue;
		}
		Book book = createBook(bookId, totalCopies);
		book.setAvailableCopies(availableCopies);
		books.push_back(book);
	}
	return !books.empty();
}

bool Frame::saveInventory(const vector<Book>& books)
{
	ofstream output(INVENTORY_FILE, ios::trunc);
	if (!output.is_open())
	{
		return false;
	}
	for (const Book& book : books)
	{
		output << book.getBookId() << '|' << book.getTotalCopies() << '|' << book.getAvailableCopies() << '\n';	// 保存书籍ID、总副本数和可用副本数	
	}
	return output.good();
}

bool Frame::saveLibraryData(const vector<Book>& books, const vector<Record>& records)
{
	const bool inventorySaved = saveInventory(books);
	const bool recordsSaved = saveRecords(records);
	return inventorySaved && recordsSaved;
}

bool Frame::restoreActiveLoans(vector<Book>& books, vector<Reader>& readers, const vector<Record>& records)
{
	bool consistent = true;
	for (const Record& record : records)
	{
		if (record.getIsReturned())
		{
			continue;
		}
		Book* book = findBook(books, record.getBookId());
		Reader* reader = findReader(readers, record.getReaderId());
		if (book == nullptr || reader == nullptr)
		{
			consistent = false;
			continue;
		}
		try
		{
			reader->borrowBook(book->getBookName());
		}
		catch (const exception&)
		{
			consistent = false;
		}
	}

	for (Book& book : books)
	{
		unsigned int activeLoans = 0;
		for (const Record& record : records)
		{
			if (!record.getIsReturned() && record.getBookId() == book.getBookId())
			{
				++activeLoans;
			}
		}
		if (activeLoans > book.getTotalCopies())
		{
			activeLoans = book.getTotalCopies();
		}
		book.setAvailableCopies(book.getTotalCopies() - activeLoans);
	}
	return consistent;
}

void Frame::showBooks(const vector<Book>& books)
{
	cout << "----- Book Catalogue (" << books.size() << " titles) -----\n";
	printBookTableHeader();
	for (const Book& book : books)
	{
		printBookRow(book);
	}
}

void Frame::showBookDetails(const Book& book, const vector<Reader>& readers, const vector<Record>& records)
{
	const string today = makeDate();
	cout << "\n===== Book Details =====\n";
	cout << "Book ID       : " << book.getBookId() << '\n';
	cout << "Title         : " << book.getBookName() << '\n';
	cout << "Author        : " << book.getAuthor() << '\n';
	cout << "Total copies  : " << book.getTotalCopies() << '\n';
	cout << "On shelf      : " << book.getAvailableCopies() << '\n';
	cout << "On loan       : " << book.getTotalCopies() - book.getAvailableCopies() << '\n';

	cout << "\nCurrent borrowers:\n";
	bool anyBorrower = false;
	for (const Reader& reader : readers)
	{
		for (const string& borrowedBook : reader.getBorrowedBooks())
		{
			if (borrowedBook == book.getBookName())
			{
				cout << "  " << reader.getReaderName() << " (Reader ID: " << reader.getReaderId() << ")\n";
				anyBorrower = true;
			}
		}
	}
	if (!anyBorrower)
	{
		cout << "  none\n";
	}

	cout << "\nBorrowing history:\n";
	bool anyRecord = false;
	for (const Record& record : records)
	{
		if (record.getBookId() != book.getBookId())
		{
			continue;
		}
		string borrowerName = "unknown reader";
		for (const Reader& reader : readers)
		{
			if (reader.getReaderId() == record.getReaderId())
			{
				borrowerName = reader.getReaderName();
				break;
			}
		}
		cout << "  Record " << record.getRecordId()
			<< " | " << borrowerName << " (ID " << record.getReaderId() << ')'
			<< " | borrowed " << record.getBorrowDate()
			<< " | due " << record.getReturnDate()
			<< " | " << (record.getIsReturned() ? "returned" : (isOverdue(record.getReturnDate(), today) ? "on loan (overdue)" : "on loan"))
			<< '\n';
		anyRecord = true;
	}
	if (!anyRecord)
	{
		cout << "  no borrowing record for this title yet\n";
	}
}

void Frame::showBookCatalogPage(const vector<Book>& books, const vector<Reader>& readers, const vector<Record>& records)
{
	if (books.empty())
	{
		cout << "The catalogue is empty.\n";
		waitForEnter();
		return;
	}

	const size_t pageCount = (books.size() + CATALOG_PAGE_SIZE - 1) / CATALOG_PAGE_SIZE;
	size_t page = 0;
	for (;;)
	{
		const size_t begin = page * CATALOG_PAGE_SIZE;
		const size_t end = min(begin + CATALOG_PAGE_SIZE, books.size());

		clearScreen();
		cout << "========== Book Catalogue ==========\n";
		printBookTableHeader();
		for (size_t index = begin; index < end; ++index)
		{
			printBookRow(books[index]);
		}
		cout << "\nPage " << page + 1 << '/' << pageCount
			<< "  |  n = next page, p = previous page, a book ID = details, 0 = back to menu\n";

		string input;
		cout << "Command: ";
		if (!getline(cin, input))
		{
			return;
		}
		input = trim(input);
		if (input.empty() || input == "0")
		{
			return;
		}
		if (input == "n" || input == "N")
		{
			if (page + 1 < pageCount)
			{
				++page;
			}
			continue;
		}
		if (input == "p" || input == "P")
		{
			if (page > 0)
			{
				--page;
			}
			continue;
		}

		unsigned int bookId = 0;
		if (!parseUnsigned(input, bookId))
		{
			cout << "\nUnknown command.\n";
			waitForEnter();
			continue;
		}
		const Book* book = findBook(books, bookId);
		if (book == nullptr)
		{
			cout << "\nNo book with ID " << bookId << " exists in the catalogue.\n";
			waitForEnter();
			continue;
		}
		showBookDetails(*book, readers, records);
		waitForEnter();
	}
}

void Frame::searchBooks(const vector<Book>& books)
{
	cout << "========== Search Books ==========\n";
	cout << "Enter a title, an author, or a book ID (0 to cancel): ";
	string keyword;
	if (!getline(cin, keyword))
	{
		return;
	}
	keyword = trim(keyword);
	if (keyword.empty() || keyword == "0")
	{
		return;
	}

	const string needle = toLowerText(keyword);
	vector<const Book*> matches;
	for (const Book& book : books)
	{
		if (to_string(book.getBookId()) == keyword
			|| toLowerText(book.getBookName()).find(needle) != string::npos
			|| toLowerText(book.getAuthor()).find(needle) != string::npos)
		{
			matches.push_back(&book);
		}
	}

	if (matches.empty())
	{
		cout << "\nNo book matches \"" << keyword << "\".\n";
		waitForEnter();
		return;
	}

	cout << "\n" << matches.size() << " matching book(s):\n";
	printBookTableHeader();
	for (const Book* book : matches)
	{
		printBookRow(*book);
	}
	waitForEnter();
}

void Frame::borrowBook(vector<Book>& books, Reader& reader, vector<Record>& records, Statistics& statistics)
{
	cout << "========== Borrow a Book ==========\n";
	showBooks(books);

	unsigned int bookId = 0;
	if (!readUnsigned("\nEnter the book ID to borrow (0 to cancel): ", bookId))
	{
		return;
	}
	if (bookId == 0)
	{
		return;
	}

	Book* book = findBook(books, bookId);
	if (book == nullptr)
	{
		cout << "Error: no book with ID " << bookId << " exists in the catalogue.\n";
		waitForEnter();
		return;
	}
	if (book->getAvailableCopies() == 0)
	{
		cout << "Error: every copy of \"" << book->getBookName() << "\" is already on loan.\n";
		waitForEnter();
		return;
	}
	for (const Record& record : records)
	{
		if (!record.getIsReturned() && record.getReaderId() == reader.getReaderId() && record.getBookId() == bookId)
		{
			cout << "Error: you have not returned your copy of \"" << book->getBookName() << "\" yet.\n";
			waitForEnter();
			return;
		}
	}
	if (reader.getTotalBorrowedBooks() >= reader.getMaxBorrowLimit())
	{
		cout << "Error: you have reached your borrowing limit of " << reader.getMaxBorrowLimit() << " books.\n";
		waitForEnter();
		return;
	}

	if (!book->borrowCopy())
	{
		cout << "Error: no copy is available any more.\n";
		waitForEnter();
		return;
	}
	try
	{
		reader.borrowBook(book->getBookName());
	}
	catch (const exception& error)
	{
		book->returnCopy();
		cout << "Error: " << error.what() << '\n';
		waitForEnter();
		return;
	}

	const string borrowDate = makeDate();
	const string dueDate = makeDate(DEFAULT_LOAN_DAYS);
	records.emplace_back(nextRecordId(records), reader.getReaderId(), bookId, borrowDate, dueDate, false);
	statistics.updateOnBorrow(*book, reader);

	cout << "\nBorrowed \"" << book->getBookName() << "\" successfully.\n"
		<< "Borrow date : " << borrowDate << '\n'
		<< "Due date    : " << dueDate << '\n'
		<< "On shelf now: " << book->getAvailableCopies() << '/' << book->getTotalCopies() << '\n';
	if (!saveLibraryData(books, records))
	{
		cout << "Warning: the library data could not be written to disk.\n";
	}
	waitForEnter();
}

void Frame::returnBook(vector<Book>& books, Reader& reader, vector<Record>& records, Statistics& statistics)
{
	const string today = makeDate();
	cout << "========== Return a Book ==========\n";
	cout << "Books currently borrowed by " << reader.getReaderName() << ":\n";

	bool anyLoan = false;
	for (const Record& record : records)
	{
		if (record.getReaderId() != reader.getReaderId() || record.getIsReturned())
		{
			continue;
		}
		const Book* loanedBook = findBook(books, record.getBookId());
		cout << "  " << record.getBookId() << " | "
			<< (loanedBook != nullptr ? loanedBook->getBookName() : string("Unknown book"))
			<< " | due " << record.getReturnDate()
			<< (isOverdue(record.getReturnDate(), today) ? "  [overdue]" : "")
			<< '\n';
		anyLoan = true;
	}
	if (!anyLoan)
	{
		cout << "\n  none\n";
		waitForEnter();
		return;
	}

	unsigned int bookId = 0;
	if (!readUnsigned("\nEnter the book ID to return (0 to cancel): ", bookId))
	{
		return;
	}
	if (bookId == 0)
	{
		return;
	}

	Book* book = findBook(books, bookId);
	if (book == nullptr)
	{
		cout << "Error: no book with ID " << bookId << " exists in the catalogue.\n";
		waitForEnter();
		return;
	}

	Record* activeRecord = nullptr;
	for (Record& record : records)
	{
		if (!record.getIsReturned() && record.getReaderId() == reader.getReaderId() && record.getBookId() == bookId)
		{
			activeRecord = &record;
			break;
		}
	}
	if (activeRecord == nullptr)
	{
		cout << "Error: you have not borrowed \"" << book->getBookName() << "\", so it cannot be returned.\n";
		waitForEnter();
		return;
	}

	activeRecord->markReturned();
	if (!book->returnCopy())
	{
		cout << "Warning: the shelf count of this title is already complete.\n";
	}
	reader.returnBook(book->getBookName());
	statistics.updateOnReturn(*book, reader);

	cout << "\nReturned \"" << book->getBookName() << "\" successfully"
		<< (isOverdue(activeRecord->getReturnDate(), today) ? " (it was overdue).\n" : ".\n")
		<< "On shelf now: " << book->getAvailableCopies() << '/' << book->getTotalCopies() << '\n';
	if (!saveLibraryData(books, records))
	{
		cout << "Warning: the library data could not be written to disk.\n";
	}
	waitForEnter();
}

void Frame::showMyRecords(const vector<Book>& books, const Reader& reader, const vector<Record>& records)
{
	const string today = makeDate();
	cout << "========== My Borrowing Records ==========\n";
	cout << "Reader         : " << reader.getReaderName() << " (ID " << reader.getReaderId() << ")\n";
	cout << "Borrowing limit: " << reader.getTotalBorrowedBooks() << '/' << reader.getMaxBorrowLimit() << '\n';

	cout << "\nBooks currently on loan:\n";
	bool anyLoan = false;
	for (const Record& record : records)
	{
		if (record.getReaderId() != reader.getReaderId() || record.getIsReturned())
		{
			continue;
		}
		const Book* book = findBook(books, record.getBookId());
		cout << "  " << record.getBookId() << " | "
			<< (book != nullptr ? book->getBookName() : string("Unknown book"))
			<< " | borrowed " << record.getBorrowDate()
			<< " | due " << record.getReturnDate()
			<< (isOverdue(record.getReturnDate(), today) ? "  [overdue]" : "")
			<< '\n';
		anyLoan = true;
	}
	if (!anyLoan)
	{
		cout << "  none\n";
	}

	cout << "\nFull borrowing history:\n";
	bool anyRecord = false;
	cout << left << setw(8) << "Record" << setw(8) << "Book"
		<< setw(TITLE_COLUMN) << "Title" << setw(13) << "Borrowed" << setw(13) << "Due" << "Status" << '\n';
	cout << string(8 + 8 + TITLE_COLUMN + 13 + 13 + 12, '-') << '\n';
	for (const Record& record : records)
	{
		if (record.getReaderId() != reader.getReaderId())
		{
			continue;
		}
		const Book* book = findBook(books, record.getBookId());
		cout << left << setw(8) << record.getRecordId()
			<< setw(8) << record.getBookId()
			<< setw(TITLE_COLUMN) << (book != nullptr ? book->getBookName() : string("Unknown book"))
			<< setw(13) << record.getBorrowDate()
			<< setw(13) << record.getReturnDate()
			<< (record.getIsReturned() ? "returned" : "on loan") << '\n';
		anyRecord = true;
	}
	if (!anyRecord)
	{
		cout << "  no borrowing record yet\n";
	}
	waitForEnter();
}

int Frame::run()
{
	vector<Book> books;
	vector<Reader> readers;
	vector<Record> records;
	Statistics statistics;

	clearScreen();
	cout << "Loading library data...\n";
	if (!loadInventory(books))
	{
		cout << INVENTORY_FILE << " was not found: building a starter catalogue of "
			<< DEFAULT_BOOK_COUNT << " titles.\n";
		buildDefaultInventory(books);
		saveInventory(books);
	}
	if (!loadReaders(readers))
	{
		cout << READERS_FILE << " was not found: creating " << DEFAULT_READER_COUNT << " demo readers.\n";
		buildDefaultReaders(readers);
		saveReaders(readers);
	}
	if (!loadRecords(records))
	{
		records.clear();
	}
	if (!restoreActiveLoans(books, readers, records))
	{
		cout << "Warning: some stored loans referred to missing readers or books and were skipped.\n";
	}
	waitForEnter();

	bool running = true;
	while (running)
	{
		unsigned int currentReaderId = 0;
		while (currentReaderId == 0)
		{
			clearScreen();
			cout << "================================================\n"
				<< "            Library Operation System\n"
				<< "================================================\n\n";
			cout << "Registered readers:\n";
			for (const Reader& reader : readers)
			{
				cout << "  " << left << setw(ID_COLUMN) << reader.getReaderId()
					<< reader.getReaderName() << '\n';
			}
			cout << "\nSign in with your reader ID, or enter 0 to quit.\n";
			unsigned int readerId = 0;
			if (!readUnsigned("Reader ID: ", readerId))
			{
				running = false;
				break;
			}
			if (readerId == 0)
			{
				running = false;
				break;
			}
			if (findReader(readers, readerId) != nullptr)
			{
				currentReaderId = readerId;
				break;
			}

			cout << "\nNo reader is registered with ID " << readerId << ".\n";
			cout << "Register a new reader instead? (y/n): ";
			string answer;
			if (!getline(cin, answer))
			{
				running = false;
				break;
			}
			answer = trim(answer);
			if (!answer.empty() && (answer[0] == 'y' || answer[0] == 'Y'))
			{
				registerReader(readers);
				if (findReader(readers, readerId) != nullptr)
				{
					currentReaderId = readerId;
				}
			}
		}
		if (!running)
		{
			break;
		}

		bool switchReader = false;
		while (!switchReader && running)
		{
			Reader* current = findReader(readers, currentReaderId);
			if (current == nullptr)
			{
				switchReader = true;
				break;
			}

			clearScreen();
			cout << "================================================\n"
				<< "            Library Operation System\n"
				<< "================================================\n";
			cout << "Signed in as " << current->getReaderName()
				<< " (ID " << current->getReaderId()
				<< ", borrowed " << current->getTotalBorrowedBooks() << '/' << current->getMaxBorrowLimit() << ")\n";
			cout << "------------------------------------------------\n"
				<< "  1. Browse the catalogue and book details\n"
				<< "  2. Search for a book\n"
				<< "  3. Borrow a book\n"
				<< "  4. Return a book\n"
				<< "  5. My borrowing records\n"
				<< "  6. Library statistics and the Top 3 Readers\n"
				<< "  7. Register a new reader\n"
				<< "  8. Switch reader\n"
				<< "  0. Save and quit\n"
				<< "------------------------------------------------\n";

			string choice;
			cout << "Your choice: ";
			if (!getline(cin, choice))
			{
				cout << '\n';
				running = false;
				break;
			}
			choice = trim(choice);
			if (choice.empty())
			{
				continue;
			}

			if (choice == "0")
			{
				running = false;
			}
			else if (choice == "1")
			{
				clearScreen();
				showBookCatalogPage(books, readers, records);
			}
			else if (choice == "2")
			{
				clearScreen();
				searchBooks(books);
			}
			else if (choice == "3")
			{
				clearScreen();
				borrowBook(books, *current, records, statistics);
			}
			else if (choice == "4")
			{
				clearScreen();
				returnBook(books, *current, records, statistics);
			}
			else if (choice == "5")
			{
				clearScreen();
				showMyRecords(books, *current, records);
			}
			else if (choice == "6")
			{
				clearScreen();
				statistics.displayStatistics(books, readers, records);
				cout << "\n---------- This session ----------\n";
				statistics.displayStatistics();
				waitForEnter();
			}
			else if (choice == "7")
			{
				clearScreen();
				registerReader(readers);
			}
			else if (choice == "8")
			{
				switchReader = true;
			}
			else
			{
				cout << "Unknown option, please try again.\n";
				waitForEnter();
			}
		}
	}

	clearScreen();
	const bool readersSaved = saveReaders(readers);
	const bool librarySaved = saveLibraryData(books, records);
	if (readersSaved && librarySaved)
	{
		cout << "Library data saved successfully.\n";
	}
	else
	{
		cout << "Warning: some library data could not be saved.\n";
	}
	cout << "Goodbye.\n";
	return 0;
}
