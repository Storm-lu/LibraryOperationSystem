#include "WutheringHeights.h"

WutheringHeights::WutheringHeights()
    : WutheringHeights(0, 0)
{
}

WutheringHeights::WutheringHeights(unsigned int id, unsigned int totalCopies)
    : Book(id, "Wuthering Heights", "Emily Bronte", totalCopies),
      specialEditionDetails("A frame-narrated Gothic novel of obsession, social division, and revenge across two generations on the Yorkshire moors."),
      summary("The intense bond between Catherine Earnshaw and Heathcliff shapes generations on the moors. Their choices leave a legacy of resentment that later characters must either repeat or overcome.")
{
}

const string& WutheringHeights::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& WutheringHeights::getSummary() const noexcept
{
    return summary;
}
