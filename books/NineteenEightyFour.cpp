#include "NineteenEightyFour.h"

NineteenEightyFour::NineteenEightyFour()
    : NineteenEightyFour(0, 0)
{
}

NineteenEightyFour::NineteenEightyFour(unsigned int id, unsigned int totalCopies)
    : Book(id, "1984", "George Orwell", totalCopies),
      specialEditionDetails("A dystopian novel about mass surveillance, manipulated language, historical revision, and authoritarian power."),
      summary("Winston Smith struggles to preserve independent thought under an all-controlling state. His private doubts and relationship with Julia bring him into conflict with the Party's effort to control both truth and loyalty.")
{
}

const string& NineteenEightyFour::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& NineteenEightyFour::getSummary() const noexcept
{
    return summary;
}
