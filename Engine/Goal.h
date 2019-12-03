#pragma once
#include "Location.h"
#include "Colors.h"
#include "Board.h"
#include "Snake.h"
#include <random>

class Goal
{
public:
	Goal();
	Goal(std::mt19937& rng, Board& brd, const Snake& snek);
	void Respawn(std::mt19937& rng, Board& brd, const Snake& snek);
	void Draw(Board& brd);
	const Location& GetLocation() const;
private:
	static constexpr Color c = Colors::Red;
protected:
	Location loc;
};

