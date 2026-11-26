#include "TheLittlePrince.h"

TheLittlePrince::TheLittlePrince()
    : TheLittlePrince(0, 0)
{
}

TheLittlePrince::TheLittlePrince(unsigned int id, unsigned int totalCopies)
    : Book(id, "The Little Prince", "Antoine de Saint-Exupery", totalCopies),
      specialEditionDetails("A fable told through a pilot's meeting with a young traveler, using visits to distant worlds to reflect on adult habits and human connection."),
      summary("A pilot meets a young traveler whose stories explore friendship, responsibility, and wonder. The prince's bond with a rose and his journey across planets shape the lessons he shares.")
{
}

const string& TheLittlePrince::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& TheLittlePrince::getSummary() const noexcept
{
    return summary;
}
