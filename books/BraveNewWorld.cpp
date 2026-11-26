#include "BraveNewWorld.h"

BraveNewWorld::BraveNewWorld()
    : BraveNewWorld(0, 0)
{
}

BraveNewWorld::BraveNewWorld(unsigned int id, unsigned int totalCopies)
    : Book(id, "Brave New World", "Aldous Huxley", totalCopies),
      specialEditionDetails("A dystopian account of a World State that uses engineered castes, conditioning, and pleasure to control its citizens."),
      summary("A dissenter questions a technologically managed society built around stability and conformity. The arrival of John, raised outside the World State, exposes the costs of trading freedom and human bonds for comfort.")
{
}

const string& BraveNewWorld::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& BraveNewWorld::getSummary() const noexcept
{
    return summary;
}
