#include "Statistics.h"

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

void Statistics::updateOnBorrow(const Book&, const Reader&) noexcept
{
	++totalBorrows;
}

void Statistics::updateOnReturn(const Book&, const Reader&) noexcept
{
	if (totalReturns < totalBorrows)
	{
		++totalReturns;
	}
}

void Statistics::displayStatistics() const
{
	cout << "Total borrow operations: " << totalBorrows << '\n'
		<< "Total return operations: " << totalReturns << '\n'
		<< "Currently borrowed copies: " << totalBorrows - totalReturns << '\n';
}

void Statistics::displayStatistics(const vector<Book>& books, const vector<Reader>& readers, const vector<Record>& records) const
{
	cout << "\n========== Book Borrowing Statistics ==========" << '\n';
	for (const Book& book : books)
	{
		unsigned int borrowCount = 0;
		for (const Record& record : records)
		{
			if (record.getBookId() == book.getBookId())
			{
				++borrowCount;
			}
		}
		cout << "Book ID: " << book.getBookId()
			<< " | Title: " << book.getBookName()
			<< " | Author: " << book.getAuthor()
			<< " | Total copies: " << book.getTotalCopies()
			<< " | Available: " << book.getAvailableCopies()
			<< " | Total borrows: " << borrowCount << '\n';
	}

	vector<pair<const Reader*, unsigned int>> readerBorrows;
	readerBorrows.reserve(readers.size());
	cout << "\n========== Reader Borrowing Statistics ==========" << '\n';
	for (const Reader& reader : readers)
	{
		unsigned int borrowCount = 0;
		for (const Record& record : records)
		{
			if (record.getReaderId() == reader.getReaderId())
			{
				++borrowCount;
			}
		}
		readerBorrows.emplace_back(&reader, borrowCount);
		cout << "Reader ID: " << reader.getReaderId()
			<< " | Name: " << reader.getReaderName()
			<< " | Currently borrowed: " << reader.getTotalBorrowedBooks() << '/' << reader.getMaxBorrowLimit()
			<< " | Total borrows: " << borrowCount << '\n';
	}

	stable_sort(readerBorrows.begin(), readerBorrows.end(), [](const auto& left, const auto& right)
		{
			if (left.second != right.second)
			{
				return left.second > right.second;
			}
			return left.first->getReaderId() < right.first->getReaderId();
		});

	cout << "\n========== Top 3 Readers ==========" << '\n';
	const size_t starCount = min<size_t>(3, readerBorrows.size());
	if (starCount == 0 || readerBorrows.front().second == 0)
	{
		cout << "No borrowing records yet.\n";
		return;
	}
	for (size_t i = 0; i < starCount; ++i)
	{
		const Reader& reader = *readerBorrows[i].first;
		cout << i + 1 << ". " << reader.getReaderName()
			<< " (Reader ID: " << reader.getReaderId()
			<< ", Total borrows: " << readerBorrows[i].second << ")\n";
	}
}

unsigned int Statistics::getTotalBorrows() const noexcept
{
	return totalBorrows;
}

unsigned int Statistics::getTotalReturns() const noexcept
{
	return totalReturns;
}
