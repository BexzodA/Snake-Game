#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(std::mt19937& rng, Board& brd, const Snake& snek, const Goal& goal)
{
	std::uniform_int_distribution<int> xDist(1, brd.GetGridWidth() - 2);
	std::uniform_int_distribution<int> yDist(1, brd.GetGridHeight() - 2);

	Location newLoc;
	do {
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snek.IsInTile(newLoc) || goal.GetLocation() == newLoc);

	loc = newLoc;
}

void Obstacle::Draw(Board& brd) const
{
	brd.DrawCell(loc, c, 2);
}
