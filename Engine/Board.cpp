#include "Board.h"
#include <assert.h>

Board::Board(Graphics& arg_gfx) :
	gfx(arg_gfx)
{
}

void Board::DrawCell(const Location& loc, Color c, int padding)
{
	//assert sends an error if the boolean expression evaluates to false
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension, c, padding);
}

void Board::DrawSnakeCell(const Location& loc, Color c, int padding)
{
	//assert sends an error if the boolean expression evaluates to false
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawSnake(loc.x * dimension, loc.y * dimension, loc.x * dimension + dimension, loc.y * dimension + dimension, c, padding);
}

int Board::GetGridWidth()
{
	return width;
}

int Board::GetGridHeight()
{
	return height;
}

bool Board::IsInsideGrid(const Location& loc) const
{
	return loc.x >= 1 && loc.y >= 1 &&
		loc.x < width - 1 && loc.y < height - 1;
}
