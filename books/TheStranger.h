#pragma once

#include "Book.h"
using namespace std;

class TheStranger : public Book
{
public:
    TheStranger();
    TheStranger(unsigned int id, unsigned int totalCopies);
    const string& getSpecialEditionDetails() const noexcept;
    const string& getDetail() const noexcept { return specialEditionDetails; }
    const string& getSummary() const noexcept;

private:
    string specialEditionDetails;
    string summary;
};
