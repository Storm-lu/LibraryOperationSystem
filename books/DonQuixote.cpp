#include "DonQuixote.h"

DonQuixote::DonQuixote()
    : DonQuixote(0, 0)
{
}

DonQuixote::DonQuixote(unsigned int id, unsigned int totalCopies)
    : Book(id, "Don Quixote", "Miguel de Cervantes", totalCopies),
      specialEditionDetails("A comic adventure that contrasts idealized chivalry with everyday life through the travels of Don Quixote and Sancho Panza."),
      summary("An aging gentleman sets out as a knight-errant with his practical squire Sancho Panza. Their misadventures explore imagination, honor, friendship, and the gap between ideals and reality.")
{
}

const string& DonQuixote::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& DonQuixote::getSummary() const noexcept
{
    return summary;
}
