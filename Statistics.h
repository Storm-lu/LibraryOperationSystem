#pragma once

#include "books/Book.h"
#include "Reader.h"
#include "Record.h"

#include <vector>

using namespace std;

class Statistics
{
	friend class Reader;
	friend class Book;
public:
	Statistics() = default;
	void updateOnBorrow(const Book& book, const Reader& reader) noexcept;
	void updateOnReturn(const Book& book, const Reader& reader) noexcept;
	void displayStatistics() const;
	void displayStatistics(const vector<Book>& books, const vector<Reader>& readers, const vector<Record>& records) const;
	unsigned int getTotalBorrows() const noexcept;
	unsigned int getTotalReturns() const noexcept;

private:
	unsigned int totalBorrows = 0;
	unsigned int totalReturns = 0;
};