#include "Reader.h"

#include <stdexcept>
#include <utility>

using namespace std;

Reader::Reader()
	: Reader(0, "", 0)
{
}

Reader::Reader(unsigned int id, string name, unsigned int maxLimit)
	: readerId(id), readerName(move(name)), maxBorrowLimit(maxLimit)
{
}

unsigned int Reader::getReaderId() const noexcept
{
	return readerId;
}

const string& Reader::getReaderName() const noexcept
{
	return readerName;
}

unsigned int Reader::getTotalBorrowedBooks() const noexcept
{
	return static_cast<unsigned int>(borrowedBooks.size());
}

unsigned int Reader::getMaxBorrowLimit() const noexcept
{
	return maxBorrowLimit;
}

const vector<string>& Reader::getBorrowedBooks() const noexcept
{
	return borrowedBooks;
}

void Reader::borrowBook(string bookName)
{
	if (borrowedBooks.size() >= maxBorrowLimit)
	{
		throw length_error("Reader has reached the borrowing limit.");
	}
	if (bookName.empty())
	{
		throw invalid_argument("Book name cannot be empty.");
	}
	for (const string& borrowedBook : borrowedBooks)
	{
		if (borrowedBook == bookName)
		{
			throw invalid_argument("This book has not been returned yet.");
		}
	}
	borrowedBooks.push_back(move(bookName));
}

void Reader::returnBook(const string& bookName)
{
	for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it)
	{
		if (*it == bookName)
		{
			borrowedBooks.erase(it);
			return;
		}
	}
}
