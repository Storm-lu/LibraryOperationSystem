#include "LesMiserables.h"

LesMiserables::LesMiserables()
    : LesMiserables(0, 0)
{
}

LesMiserables::LesMiserables(unsigned int id, unsigned int totalCopies)
    : Book(id, "Les Miserables", "Victor Hugo", totalCopies),
      specialEditionDetails("A broad social novel connecting poverty, justice, mercy, and revolution through the lives of people in nineteenth-century France."),
      summary("Jean Valjean seeks a new life amid injustice and political unrest in nineteenth-century France. Pursued by Inspector Javert, he tries to protect Cosette while the characters are swept into wider struggles for change.")
{
}

const string& LesMiserables::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& LesMiserables::getSummary() const noexcept
{
    return summary;
}
