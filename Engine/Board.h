#pragma once

#include "Graphics.h"
#include "Colors.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& arg_gfx);
	void DrawCell(const Location& loc, Color c, int padding);
	void DrawSnakeCell(const Location& loc, Color c, int padding);
	int GetGridWidth();
	int GetGridHeight();
	bool IsInsideGrid(const Location& loc) const;
private:
	static constexpr int dimension = 20;
	static constexpr int width = 40;
	static constexpr int height = 30;
	Graphics& gfx;
};

