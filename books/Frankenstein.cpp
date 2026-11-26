#include "Frankenstein.h"

Frankenstein::Frankenstein()
    : Frankenstein(0, 0)
{
}

Frankenstein::Frankenstein(unsigned int id, unsigned int totalCopies)
    : Book(id, "Frankenstein", "Mary Shelley", totalCopies),
      specialEditionDetails("A Gothic novel about scientific ambition, isolation, and the responsibilities owed to a created life."),
      summary("Victor Frankenstein faces the consequences of creating a sentient being. Rejected by his creator and society, the creature seeks companionship and demands that Victor answer for his choices.")
{
}

const string& Frankenstein::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& Frankenstein::getSummary() const noexcept
{
    return summary;
}
