#include "MobyDick.h"

MobyDick::MobyDick()
    : MobyDick(0, 0)
{
}

MobyDick::MobyDick(unsigned int id, unsigned int totalCopies)
    : Book(id, "Moby-Dick", "Herman Melville", totalCopies),
      specialEditionDetails("A sea voyage combining the pursuit of a whale with reflections on obsession, fate, labor, and the natural world."),
      summary("Captain Ahab leads the Pequod crew on a consuming hunt for the white whale. Narrated by Ishmael, the voyage moves between shipboard life, maritime lore, and Ahab's fixation on revenge.")
{
}

const string& MobyDick::getSpecialEditionDetails() const noexcept
{
    return specialEditionDetails;
}

const string& MobyDick::getSummary() const noexcept
{
    return summary;
}
