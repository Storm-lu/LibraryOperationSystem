#include "TheLordOfTheRings.h"

TheLordOfTheRings::TheLordOfTheRings()
    : TheLordOfTheRings(0, 0)
{
}

TheLordOfTheRings::TheLordOfTheRings(unsigned int id, unsigned int totalCopies)
    : Book(id, "The Lord of the Rings", "J. R. R. Tolkien", totalCopies),
      specialEditionDetails("An epic fantasy about a dangerous journey, the burden of power, and the alliances needed to resist Sauron."),
      summary("A fellowship undertakes a perilous journey to destroy a powerful ring. Frodo and his companions face temptation and loss as the fate of Middle-earth depends on their choices.")
{
}

const string& TheLordOfTheRings::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& TheLordOfTheRings::getSummary() const noexcept
{
    return summary;
}
