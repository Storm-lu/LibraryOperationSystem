#include "DreamOfTheRedChamber.h"

DreamOfTheRedChamber::DreamOfTheRedChamber()
    : DreamOfTheRedChamber(0, 0)
{
}

DreamOfTheRedChamber::DreamOfTheRedChamber(unsigned int id, unsigned int totalCopies)
    : Book(id, "Dream of the Red Chamber", "Cao Xueqin", totalCopies),
      specialEditionDetails("A detailed portrait of Qing-era family life, following the Jia household, its relationships, customs, and decline."),
      summary("The rise and decline of the Jia family is told through the lives of its young members. The relationships of Jia Baoyu, Lin Daiyu, and Xue Baochai anchor a story of love, status, and impermanence.")
{
}

const string& DreamOfTheRedChamber::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& DreamOfTheRedChamber::getSummary() const noexcept
{
    return summary;
}
