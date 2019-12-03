#include "Goal.h"

Goal::Goal(std::mt19937& rng, Board& brd, const Snake& snek)
{
	Respawn(rng, brd, snek);
}

Goal::Goal() {
	loc.x = 5;
	loc.y = 5;
}

void Goal::Respawn(std::mt19937& rng, Board& brd, const Snake& snek)
{
	std::uniform_int_distribution<int> xDist(1, brd.GetGridWidth() - 2);
	std::uniform_int_distribution<int> yDist(1, brd.GetGridHeight() - 2);

	Location newLoc;
	do {
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snek.IsInTile(newLoc));
	loc = newLoc;
}

void Goal::Draw(Board& brd) {
	brd.DrawCell(loc, c, 2);
}

const Location& Goal::GetLocation() const {
	return loc;
}