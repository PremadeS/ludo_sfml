#include"Board.h"
Board::Board():squares{nullptr},size{make_pair(0,0)}{}
void Board::initializeBoard()
{
	squares = new Square * [boxes];
	for (int i = 0; i < boxes; ++i)
	{
		squares[i] = new Square[cells];
		for (int j = 0; j < cells; ++j)
			squares[i][j].position = make_pair(i, j);
		
		squares[i][3].isSafe = squares[i][8].isSafe = true;
	}
	size = make_pair(boxes, cells);
}
Square Board::getSquare(pair<int, int> _pos)const { return squares[_pos.first][_pos.second]; }
bool Board::isSquareOccupied(pair<int, int> _pos)const{return squares[_pos.first][_pos.second].isOccupied; }
bool Board::isSafeSquare(pair<int, int> _pos)const{ return squares[_pos.first][_pos.second].isSafe; }


