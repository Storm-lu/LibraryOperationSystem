#include "HarryPotterAndThePhilosophersStone.h"

HarryPotterAndThePhilosophersStone::HarryPotterAndThePhilosophersStone()
    : HarryPotterAndThePhilosophersStone(0, 0)
{
}

HarryPotterAndThePhilosophersStone::HarryPotterAndThePhilosophersStone(unsigned int id, unsigned int totalCopies)
    : Book(id, "Harry Potter and the Philosophers Stone", "J. K. Rowling", totalCopies),
      specialEditionDetails("The opening story of Harry's life at Hogwarts, introducing wizarding society, his new friends, and the mystery of a guarded magical object."),
      summary("Harry discovers the wizarding world and begins his education at Hogwarts. With Ron and Hermione, he investigates the Philosopher's Stone and learns more about the past that shaped him.")
{
}

const string& HarryPotterAndThePhilosophersStone::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& HarryPotterAndThePhilosophersStone::getSummary() const noexcept
{
    return summary;
}
