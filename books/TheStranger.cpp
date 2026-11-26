#include "TheStranger.h"

TheStranger::TheStranger()
    : TheStranger(0, 0)
{
}

TheStranger::TheStranger(unsigned int id, unsigned int totalCopies)
    : Book(id, "The Stranger", "Albert Camus", totalCopies),
      specialEditionDetails("A novel of alienation and absurdity that follows Meursault's emotionally detached response to social and moral expectations."),
      summary("Meursault recounts an unexpected crime and his detached confrontation with society. During his trial, others judge not only his actions but also his refusal to perform expected emotions.")
{
}

const string& TheStranger::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& TheStranger::getSummary() const noexcept
{
    return summary;
}
