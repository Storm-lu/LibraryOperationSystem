#include "SherlockHolmes.h"

SherlockHolmes::SherlockHolmes()
    : SherlockHolmes(0, 0)
{
}

SherlockHolmes::SherlockHolmes(unsigned int id, unsigned int totalCopies)
    : Book(id, "The Adventures of Sherlock Holmes", "Arthur Conan Doyle", totalCopies),
      specialEditionDetails("A collection of detective adventures that showcase Holmes's observation, reasoning, and partnership with Dr Watson."),
      summary("Detective Sherlock Holmes and Dr Watson investigate a series of puzzling cases. Their inquiries uncover motives and evidence hidden beneath the surface of everyday life in London and beyond.")
{
}

const string& SherlockHolmes::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& SherlockHolmes::getSummary() const noexcept
{
    return summary;
}
