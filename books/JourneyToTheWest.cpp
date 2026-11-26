#include "JourneyToTheWest.h"

JourneyToTheWest::JourneyToTheWest()
    : JourneyToTheWest(0, 0)
{
}

JourneyToTheWest::JourneyToTheWest(unsigned int id, unsigned int totalCopies)
    : Book(id, "Journey to the West", "Wu Cheng-en", totalCopies),
      specialEditionDetails("A mythic pilgrimage blending Buddhist themes, Chinese folklore, monsters, and the adventures of the pilgrims."),
      summary("The monk Xuanzang travels west with a group of supernatural companions. Sun Wukong, Zhu Bajie, and Sha Wujing help him face trials that test discipline, loyalty, and perseverance.")
{
}

const string& JourneyToTheWest::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& JourneyToTheWest::getSummary() const noexcept
{
    return summary;
}
