#include "Dracula.h"

Dracula::Dracula()
    : Dracula(0, 0)
{
}

Dracula::Dracula(unsigned int id, unsigned int totalCopies)
    : Book(id, "Dracula", "Bram Stoker", totalCopies),
      specialEditionDetails("An epistolary Gothic horror novel told through letters, diaries, and records of a group confronting a vampire."),
      summary("Letters and journals record the effort to stop Count Dracula from spreading his influence. Mina, Jonathan, and their allies follow the clues across England and Transylvania to protect those in danger.")
{
}

const string& Dracula::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& Dracula::getSummary() const noexcept
{
    return summary;
}
