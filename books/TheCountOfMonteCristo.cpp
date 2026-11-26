#include "TheCountOfMonteCristo.h"

TheCountOfMonteCristo::TheCountOfMonteCristo()
    : TheCountOfMonteCristo(0, 0)
{
}

TheCountOfMonteCristo::TheCountOfMonteCristo(unsigned int id, unsigned int totalCopies)
    : Book(id, "The Count of Monte Cristo", "Alexandre Dumas", totalCopies),
      specialEditionDetails("An adventure of wrongful imprisonment, escape, reinvention, and revenge, set against the social world of nineteenth-century France."),
      summary("Edmond Dantes escapes wrongful imprisonment and pursues a carefully planned reckoning. As the Count of Monte Cristo, he tests the limits of justice, loyalty, and vengeance.")
{
}

const string& TheCountOfMonteCristo::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& TheCountOfMonteCristo::getSummary() const noexcept
{
    return summary;
}
