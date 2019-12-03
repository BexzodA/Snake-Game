#pragma once
#include "Board.h"
#include <assert.h>
#include <random>

class Snake
{
private:
	class Segement {
	public:
		void InitHead( const Location& a_loc);
		void InitBody(std::mt19937& rng, int uSeg);
		void Follow(const Segement& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& board, int padding) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow(std::mt19937& rng);
	void Draw(Board& board) const;
	Location GetNextHeadLocation(const Location delta_loc);
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int MaxSegements = 99;
	int usedSegements = 1;
	Segement segements[99];

};

