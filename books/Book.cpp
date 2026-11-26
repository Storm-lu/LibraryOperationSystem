#include "Book.h"

#include <stdexcept>
#include <utility>

using namespace std;

Book::Book()
	: Book(0, "", "", 0)
{
}

Book::Book(unsigned int id, string name, string authorName, unsigned int totalCopies)
	: bookId(id),
	  bookName(move(name)),
	  author(move(authorName)),
	  totalCopies(totalCopies),
	  availableCopies(totalCopies)
{
}

unsigned int Book::getBookId() const noexcept
{
	return bookId;
}

const string& Book::getBookName() const noexcept
{
	return bookName;
}

const string& Book::getAuthor() const noexcept
{
	return author;
}

unsigned int Book::getTotalCopies() const noexcept
{
	return totalCopies;
}

unsigned int Book::getAvailableCopies() const noexcept
{
	return availableCopies;
}

void Book::setAvailableCopies(unsigned int copies)
{
	if (copies > totalCopies)
	{
		throw out_of_range("Available copies cannot exceed total copies.");//如果传入的可用副本数大于总副本数，则抛出异常，提示错误信息
	}
	availableCopies = copies;
}

bool Book::borrowCopy() noexcept
{
	if (availableCopies == 0)//如果没有可用副本，则借阅失败，返回false
	{
		return false;
	}
	--availableCopies;
	return true;
}

bool Book::returnCopy() noexcept
{
	if (availableCopies >= totalCopies)
	{
		return false;
	}
	++availableCopies;
	return true;
}