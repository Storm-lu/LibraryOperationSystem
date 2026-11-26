#pragma once

#include "Book.h"
using namespace std;

class JaneEyre : public Book
{
public:
    JaneEyre();
    JaneEyre(unsigned int id, unsigned int totalCopies);
    const string& getSpecialEditionDetails() const noexcept;
    const string& getDetail() const noexcept { return specialEditionDetails; }
    const string& getSummary() const noexcept;

private:
    string specialEditionDetails;
    string summary;
};
