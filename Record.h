#pragma once

#include <string>

using namespace std;

class Record
{
public:
	Record();
	Record(unsigned int recordId, unsigned int readerId, unsigned int bookId, string borrowDate, string returnDate, bool returned);
	unsigned int getRecordId() const noexcept;
	unsigned int getReaderId() const noexcept;
	unsigned int getBookId() const noexcept;
	const string& getBorrowDate() const noexcept;
	const string& getReturnDate() const noexcept;
	bool getIsReturned() const noexcept;
	void markReturned() noexcept;
	void markBorrowed() noexcept;

private:
	unsigned int recordId;
	unsigned int readerId;
	unsigned int bookId;
	string borrowDate;
	string returnDate;
	bool isReturned;
};