#include "CrimeAndPunishment.h"

CrimeAndPunishment::CrimeAndPunishment()
    : CrimeAndPunishment(0, 0)
{
}

CrimeAndPunishment::CrimeAndPunishment(unsigned int id, unsigned int totalCopies)
    : Book(id, "Crime and Punishment", "Fyodor Dostoevsky", totalCopies),
      specialEditionDetails("A psychological novel examining guilt, moral responsibility, poverty, and the possibility of redemption in nineteenth-century St Petersburg."),
      summary("A former student confronts guilt after committing a murder in St Petersburg. His attempts to justify the crime are challenged by an investigator and by his growing bond with Sonia.")
{
}

const string& CrimeAndPunishment::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& CrimeAndPunishment::getSummary() const noexcept
{
    return summary;
}
