#pragma once
#include <iostream>
#include "Player.h"
using namespace std;

class Player;
class Piece
{
private:
	string pieceID;
	pair<int, int> piecePos;
	bool locked;
	bool roundTrip;
	bool pugGai;
	Player* player;
public:
	Piece();
	Piece(string _ID, pair<int, int> _pos, Player* _player);
	void moveToPos(pair<int,int> _pos);
	string getPieceID()const;
	Player* getPlayer();
	pair<int, int> getPiecePos()const;
	void setRoundTrip(bool val);
	bool getRoundTrip()const;
	bool isLocked()const;
	void setLock(bool val);
	void setPugGai(bool val);
	bool getPugGai();

};

