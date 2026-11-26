#include "TheAlchemist.h"

TheAlchemist::TheAlchemist()
    : TheAlchemist(0, 0)
{
}

TheAlchemist::TheAlchemist(unsigned int id, unsigned int totalCopies)
    : Book(id, "The Alchemist", "Paulo Coelho", totalCopies),
      specialEditionDetails("A symbolic travel narrative centered on dreams, omens, self-discovery, and the idea of pursuing one's purpose."),
      summary("A young shepherd travels in search of treasure and learns to interpret his life journey. Encounters along the way teach Santiago to listen, take risks, and understand what he values.")
{
}

const string& TheAlchemist::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& TheAlchemist::getSummary() const noexcept
{
    return summary;
}
