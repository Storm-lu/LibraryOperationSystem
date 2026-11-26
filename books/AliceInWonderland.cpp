#include "AliceInWonderland.h"

AliceInWonderland::AliceInWonderland()
    : AliceInWonderland(0, 0)
{
}

AliceInWonderland::AliceInWonderland(unsigned int id, unsigned int totalCopies)
    : Book(id, "Alice Adventures in Wonderland", "Lewis Carroll", totalCopies),
      specialEditionDetails("A dreamlike Victorian fantasy that combines playful logic, poems, and wordplay."),
      summary("Alice follows a white rabbit into a dreamlike world of curious creatures and wordplay. Her encounters with the Cheshire Cat, the Mad Hatter, and the Queen of Hearts turn ordinary rules upside down.")
{
}

const string& AliceInWonderland::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& AliceInWonderland::getSummary() const noexcept
{
    return summary;
}
