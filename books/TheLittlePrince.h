#pragma once

#include "Book.h"
using namespace std;

class TheLittlePrince : public Book
{
public:
    TheLittlePrince();
    TheLittlePrince(unsigned int id, unsigned int totalCopies);
    const string& getSpecialEditionDetails() const noexcept;
    const string& getDetail() const noexcept { return specialEditionDetails; }
    const string& getSummary() const noexcept;

private:
    string specialEditionDetails;
    string summary;
};
