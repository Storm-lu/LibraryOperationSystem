#include "TheGreatGatsby.h"

TheGreatGatsby::TheGreatGatsby()
    : TheGreatGatsby(0, 0)
{
}

TheGreatGatsby::TheGreatGatsby(unsigned int id, unsigned int totalCopies)
    : Book(id, "The Great Gatsby", "F. Scott Fitzgerald", totalCopies),
      specialEditionDetails("A portrait of wealth, class, longing, and disillusionment among the privileged during the Jazz Age."),
      summary("Nick Carraway observes Jay Gatsby's pursuit of wealth and a lost love in Jazz Age America. Gatsby's parties and ambitions reveal the distance between his dream and the society he hopes to enter.")
{
}

const string& TheGreatGatsby::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& TheGreatGatsby::getSummary() const noexcept
{
    return summary;
}
