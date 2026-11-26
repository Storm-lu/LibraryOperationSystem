#include "TheMoonAndSixpence.h"

TheMoonAndSixpence::TheMoonAndSixpence()
	: TheMoonAndSixpence(0, 0)
{
}

TheMoonAndSixpence::TheMoonAndSixpence(unsigned int id, unsigned int totalCopies)
	: Book(id, "The Moon and Sixpence", "W. Somerset Maugham", totalCopies),
	  specialEditionDetails("A novel about Charles Strickland's break with convention and his increasingly consuming pursuit of painting."),
	  summary("An English stockbroker abandons his life to pursue painting in Paris and Tahiti. The people around him struggle to understand the cost of his artistic ambition and refusal to conform.")
{
}

const string& TheMoonAndSixpence::getSpecialEditionDetails() const noexcept
{
	return specialEditionDetails;
}

const string& TheMoonAndSixpence::getSummary() const noexcept
{
	return summary;
}