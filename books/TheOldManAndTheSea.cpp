#include "TheOldManAndTheSea.h"

TheOldManAndTheSea::TheOldManAndTheSea()
    : TheOldManAndTheSea(0, 0)
{
}

TheOldManAndTheSea::TheOldManAndTheSea(unsigned int id, unsigned int totalCopies)
    : Book(id, "The Old Man and the Sea", "Ernest Hemingway", totalCopies),
      specialEditionDetails("A spare sea narrative about endurance, skill, pride, and a fisherman's relationship with the natural world."),
      summary("An aging Cuban fisherman undertakes a solitary struggle with a great marlin. His return, marked by loss as well as persistence, tests how victory and defeat should be measured.")
{
}

const string& TheOldManAndTheSea::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& TheOldManAndTheSea::getSummary() const noexcept
{
    return summary;
}
