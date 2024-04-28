#pragma once
#include "Piece.h"
#include "Team.h"
#include <string>
class Piece;
class Team;
class Player {
	string playerID;
	Piece **pieces;
	int pieceCount;
	Team* team;
public:
	Player();
	Player(string _ID, int _count,Team* _team);
	int getPieceCount();
	string getPlayerID()const;
	Piece** getPieces()const;
	void movePiece(string _pieceID,pair<int,int> _pos);
	Team* getTeam();
	void setPieceCount(int count);
};

