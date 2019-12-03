#include "Snake.h"
#include <random>

Snake::Snake(const Location& loc)
{
	segements[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = usedSegements - 1; i > 0; i--) {
		segements[i].Follow(segements[i - 1]);
	}
	segements[0].MoveBy(delta_loc);
}

void Snake::Grow(std::mt19937& rng)
{
	if (usedSegements < MaxSegements) {
		segements[usedSegements].InitBody(rng, usedSegements);
		usedSegements++;	
	}
}

void Snake::Draw(Board& board) const
{
	for (int i = 0; i < usedSegements; i++) {
		segements[i].Draw(board, (i < 19 ? i/4 : 19/4) + 2);
	}
}

Location Snake::GetNextHeadLocation(const Location delta_loc)
{
	Location l(segements[0].GetLocation());
	l.AddDeltaLoc(delta_loc);
	return l;
}

bool Snake::IsInTileExceptEnd(const Location& target) const
{
	for (int i = 0; i < usedSegements - 1; i++) {
		if (segements[i].GetLocation() == target) {
			return true;
		}
	}
	return false;	
}

bool Snake::IsInTile(const Location& target) const {
	for (int i = 0; i < usedSegements; i++) {
		if (segements[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}

void Snake::Segement::InitHead(const Location& a_loc)
{
	loc = a_loc;
	c = Snake::headColor;
}

void Snake::Segement::InitBody(std::mt19937& rng, int uSeg)
{
	std::uniform_int_distribution<int> gDist(100, 255);
	std::uniform_int_distribution<int> rbDist(1, 10);
	//c = Color(rbDist(rng),gDist(rng),rbDist(rng));
	c = Color(0, 255 - uSeg * 10 > 100 ? 255 - uSeg * 10 : 100, 0);
}

void Snake::Segement::Follow(const Segement& next)
{
	loc = next.loc;
}

void Snake::Segement::MoveBy(const Location& delta_loc)
{
	assert(std::abs(delta_loc.x) + std::abs(delta_loc.y) == 1);
	loc.AddDeltaLoc(delta_loc);
}

void Snake::Segement::Draw(Board& board, int padding) const
{
	board.DrawSnakeCell(loc, c, padding);
}

const Location& Snake::Segement::GetLocation() const
{
	return loc;
}
