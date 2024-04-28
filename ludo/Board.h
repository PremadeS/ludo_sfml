#pragma once
#define boxes 6
#define cells 18
#include "Square.h"
class Board {
	Square** squares;
	pair<int, int> size;
public:
	Board();
	void initializeBoard();
	Square getSquare(pair<int,int>_pos)const;
	bool isSquareOccupied(pair<int,int> _pos)const;
	bool isSafeSquare(pair<int,int> _pos)const;
};
