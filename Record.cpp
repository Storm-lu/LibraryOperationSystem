#include "Record.h"

#include <utility>

using namespace std;

Record::Record()
	: Record(0, 0, 0, "", "", false)
{
}

Record::Record(unsigned int recordId, unsigned int readerId, unsigned int bookId, string borrowDate, string returnDate, bool returned)
	: recordId(recordId),
	  readerId(readerId),
	  bookId(bookId),
	  borrowDate(move(borrowDate)),
	  returnDate(move(returnDate)),
	  isReturned(returned)
{
}

unsigned int Record::getRecordId() const noexcept
{
	return recordId;
}

unsigned int Record::getReaderId() const noexcept
{
	return readerId;
}

unsigned int Record::getBookId() const noexcept
{
	return bookId;	//简单返回一个整数值，表示记录的书籍ID
}

const string& Record::getBorrowDate() const noexcept
{
	return borrowDate;
}	

const string& Record::getReturnDate() const noexcept
{
	return returnDate;
}

bool Record::getIsReturned() const noexcept
{
	return isReturned;
}

void Record::markReturned() noexcept
{
	isReturned = true;
}

void Record::markBorrowed() noexcept
{
	isReturned = false;
}

