#include "WarAndPeace.h"

WarAndPeace::WarAndPeace()
    : WarAndPeace(0, 0)
{
}

WarAndPeace::WarAndPeace(unsigned int id, unsigned int totalCopies)
    : Book(id, "War and Peace", "Leo Tolstoy", totalCopies),
      specialEditionDetails("A historical epic interweaving family life, personal change, and the upheaval of Napoleon's campaigns in Russia."),
      summary("Several Russian families experience love and upheaval during the Napoleonic wars. Their private choices unfold alongside battles and reflections on history, leadership, and chance.")
{
}

const string& WarAndPeace::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& WarAndPeace::getSummary() const noexcept
{
    return summary;
}
