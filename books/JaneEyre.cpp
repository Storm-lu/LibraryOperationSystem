#include "JaneEyre.h"

JaneEyre::JaneEyre()
    : JaneEyre(0, 0)
{
}

JaneEyre::JaneEyre(unsigned int id, unsigned int totalCopies)
    : Book(id, "Jane Eyre", "Charlotte Bronte", totalCopies),
      specialEditionDetails("A first-person account of an orphan's search for dignity, independence, love, and moral self-determination."),
      summary("An orphaned governess seeks independence and love while uncovering secrets at Thornfield Hall. Jane's choices test her principles as she confronts class barriers and the limits placed on women.")
{
}

const string& JaneEyre::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& JaneEyre::getSummary() const noexcept
{
    return summary;
}
