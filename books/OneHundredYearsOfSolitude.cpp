#include "OneHundredYearsOfSolitude.h"

OneHundredYearsOfSolitude::OneHundredYearsOfSolitude()
    : OneHundredYearsOfSolitude(0, 0)
{
}

OneHundredYearsOfSolitude::OneHundredYearsOfSolitude(unsigned int id, unsigned int totalCopies)
    : Book(id, "One Hundred Years of Solitude", "Gabriel Garcia Marquez", totalCopies),
      specialEditionDetails("A multigenerational story of the Buendia family that blends the history of Macondo with myth, memory, and political change."),
      summary("The Buendia family story unfolds across generations in the town of Macondo. Repeating names and patterns connect private lives to the town's rise, isolation, and eventual decline.")
{
}

const string& OneHundredYearsOfSolitude::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& OneHundredYearsOfSolitude::getSummary() const noexcept
{
    return summary;
}
