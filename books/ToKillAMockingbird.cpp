#include "ToKillAMockingbird.h"

ToKillAMockingbird::ToKillAMockingbird()
    : ToKillAMockingbird(0, 0)
{
}

ToKillAMockingbird::ToKillAMockingbird(unsigned int id, unsigned int totalCopies)
    : Book(id, "To Kill a Mockingbird", "Harper Lee", totalCopies),
      specialEditionDetails("A coming-of-age story addressing racial injustice, empathy, and childhood through Scout Finch's view of her community."),
      summary("Scout Finch witnesses her father defend a Black man accused of a crime in the American South. The trial and events around it challenge Scout's understanding of fairness, courage, and compassion.")
{
}

const string& ToKillAMockingbird::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& ToKillAMockingbird::getSummary() const noexcept
{
    return summary;
}
