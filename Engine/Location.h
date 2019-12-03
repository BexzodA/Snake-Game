#pragma once
struct Location {
	void AddDeltaLoc(const Location& loc) {
		x += loc.x;
		y += loc.y;
	}
	bool operator==(const Location& rightside) const {
		return x == rightside.x && y == rightside.y;
	}
	int x;
	int y;
};
