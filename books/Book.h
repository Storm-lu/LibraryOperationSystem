#pragma once

#include <string>

using namespace std;

class Book
{
public:
	Book();
	Book(unsigned int id, string name, string authorName, unsigned int totalCopies);
	virtual ~Book() = default;

	unsigned int getBookId() const noexcept;
	const string& getBookName() const noexcept;	//使用const string&返回字符串引用，避免不必要的拷贝，提高性能
	const string& getAuthor() const noexcept;	//使用const noexcept返回引用，保证不会修改对象，提高安全性
	unsigned int getTotalCopies() const noexcept;	
	unsigned int getAvailableCopies() const noexcept;
	void setAvailableCopies(unsigned int copies);
	bool borrowCopy() noexcept;
	bool returnCopy() noexcept;

private:
	unsigned int bookId;
	string bookName;
	string author;
	unsigned int totalCopies;
	unsigned int availableCopies;
};