#pragma once
#include "Goal.h"
#include "Board.h"

class Obstacle : public Goal
{
public:
	Obstacle();
	Obstacle(std::mt19937& rng, Board& brd, const Snake& snek, const Goal& goal);
	void Respawn() {};
	void Draw(Board& brd) const;
private:
	static constexpr Color c = Colors::Gray;
};

