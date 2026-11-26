#include "CatcherInTheRye.h"

CatcherInTheRye::CatcherInTheRye()
    : CatcherInTheRye(0, 0)
{
}

CatcherInTheRye::CatcherInTheRye(unsigned int id, unsigned int totalCopies)
    : Book(id, "The Catcher in the Rye", "J. D. Salinger", totalCopies),
      specialEditionDetails("A first-person coming-of-age novel about grief, loneliness, adolescence, and resistance to adult expectations."),
      summary("Holden Caulfield recounts several days of alienation and uncertainty in New York. After leaving his school, he searches for connection while struggling with grief and the transition to adulthood.")
{
}

const string& CatcherInTheRye::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& CatcherInTheRye::getSummary() const noexcept
{
    return summary;
}
