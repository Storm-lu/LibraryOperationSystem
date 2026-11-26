#pragma once

#include <string>
#include <vector>

using namespace std;

class Reader
{
public:
	Reader();
	Reader(unsigned int id, string name, unsigned int maxLimit);
	unsigned int getReaderId() const noexcept;
	const string& getReaderName() const noexcept;
	unsigned int getTotalBorrowedBooks() const noexcept;
	unsigned int getMaxBorrowLimit() const noexcept;
	const vector<string>& getBorrowedBooks() const noexcept;
	void borrowBook(string bookName);
	void returnBook(const string& bookName);
	virtual ~Reader() = default;

private:
	unsigned int readerId;
	string readerName;
	unsigned int maxBorrowLimit;
	vector<string> borrowedBooks;
};