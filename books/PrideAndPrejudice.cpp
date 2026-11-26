#include "PrideAndPrejudice.h"

PrideAndPrejudice::PrideAndPrejudice()
    : PrideAndPrejudice(0, 0)
{
}

PrideAndPrejudice::PrideAndPrejudice(unsigned int id, unsigned int totalCopies)
    : Book(id, "Pride and Prejudice", "Jane Austen", totalCopies),
      specialEditionDetails("A comedy of manners exploring courtship, social class, family obligations, and the danger of judging by appearances."),
      summary("Elizabeth Bennet and Mr Darcy navigate manners, family expectations, and first impressions. As each revises an early judgment, both must confront pride, prejudice, and the pressures of marriage and status.")
{
}

const string& PrideAndPrejudice::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& PrideAndPrejudice::getSummary() const noexcept
{
    return summary;
}
