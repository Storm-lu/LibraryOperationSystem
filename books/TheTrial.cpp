#include "TheTrial.h"

TheTrial::TheTrial()
    : TheTrial(0, 0)
{
}

TheTrial::TheTrial(unsigned int id, unsigned int totalCopies)
    : Book(id, "The Trial", "Franz Kafka", totalCopies),
      specialEditionDetails("An unsettling account of bureaucracy, power, and anxiety, built around an unexplained arrest and an inaccessible court system."),
      summary("Josef K. faces an opaque legal process without learning the nature of his alleged offense. His attempts to find answers lead deeper into a system whose rules and authority remain out of reach.")
{
}

const string& TheTrial::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& TheTrial::getSummary() const noexcept
{
    return summary;
}
