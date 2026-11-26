#include "TheHobbit.h"

TheHobbit::TheHobbit()
    : TheHobbit(0, 0)
{
}

TheHobbit::TheHobbit(unsigned int id, unsigned int totalCopies)
    : Book(id, "The Hobbit", "J. R. R. Tolkien", totalCopies),
      specialEditionDetails("A fantasy quest that follows Bilbo from a quiet home into a wider world of dwarves, dragons, riddles, and danger."),
      summary("Bilbo Baggins joins a company of dwarves on a journey to reclaim their mountain home. The unexpected adventure tests his courage and resourcefulness and changes his sense of home.")
{
}

const string& TheHobbit::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& TheHobbit::getSummary() const noexcept
{
    return summary;
}
