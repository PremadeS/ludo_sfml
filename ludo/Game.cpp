#include"Game.h"
#define boxSize 29
Game::Game(sf::RenderWindow& _window) :window{ _window }, currentPlayer{ nullptr }, teams{ nullptr }, teamCount{} {}
Board Game::startGame(int _playerCount, int _pieceCount, int _teamCount, Player**& _players)
{
	teamCount = _teamCount;
	Board board;
	board.initializeBoard();
	if (_teamCount != 0)
	{
		int teamSize = _playerCount / _teamCount;
		int teamIndex = 0;
		teams = new Team * [_teamCount];
		for (int i = 0; i < _teamCount; ++i)
			teams[i] = new Team(to_string(i));


		_players = new Player * [_playerCount];
		for (int i = 0; i < _playerCount; ++i)
		{
			if (i % teamSize == 0&&i>0)
				++teamIndex;
			_players[i] = new Player(to_string(i), _pieceCount,teams[teamIndex]);
			teams[teamIndex]->addPlayer(_players[i]);
		}
	}
	else
	{
		_players = new Player * [_playerCount];
		for (int i = 0; i < _playerCount; ++i)
			_players[i] = new Player(to_string(i), _pieceCount, nullptr); //No teams if teamCount = 0 i.e solo :)
	}
		
	return board;
}
bool Game::checkLegalMoves(Player* _currPlayer)
{
	Piece** currPieces = _currPlayer->getPieces();
	int totalPieces = _currPlayer->getPieceCount();
	if (_currPlayer->getTeam() == nullptr)
	{
		for (int i = 0; i < totalPieces; ++i)
		{
			if (!currPieces[i]->isLocked())
				return true;
		}
	}
	else
	{
		vector<Player*> players = _currPlayer->getTeam()->getPlayers();
		for (int i = 0; i < players.size(); ++i)
		{
			Piece** currPieces = players[i]->getPieces();
			int totalPieces = players[i]->getPieceCount();
			for (int j = 0; j < totalPieces; ++j)
			{
				if (!currPieces[j]->isLocked())
					return true;
			}
		}

	}
	return false;
}
void Game::posToIndex(int x,int y,int &r, int &c)
{
	if (x >= 316 && x <= 403 && y >= 458 && y <= 638)
	{
		r = 0;
		if (x >= 375 && x <= 400 && y >= 461 && y <= 638)
		{
			c = (y - 461) / 29;
		}
		else if (x >= 346 && x <= 375 && y >= 609 && y <= 638)
			c = 6;
		else if (x >= 316 && x <= 345 && y >= 461 && y <= 638)
		{
			c = 12 - (y - 461) / 29;
		}
		else
			c = 17 - (y - 461) / 29;

	}
	else if (x >= 137 && x <= 316 && y >= 374 && y <= 460)
	{
		r = 1;
		if (x >= 139 && x <= 313 && y >= 435 && y <= 458)
		{
			c = 5 - (x - 139) / boxSize;

		}
		else if (x >= 138 && x <= 317 && y >= 373 && y <= 402)
		{
			c = 7 + (x - 138) / boxSize;

		}
		else if (x >= 137 && x <= 167 && y >= 401 && y <= 430)
		{
			c = 6;

		}
		else
		{
			c = 12 + (x - 138) / boxSize;

		}
	}
	else if (x>=137&&x<=314&&y>=258&&y<=342)
	{
		r = 2;
		if (x >= 139 && x <= 313 && y >= 319 && y <= 342)
		{
			c = 5 - (x - 139) / boxSize;
		}
		else if (x >= 138 && x <= 317 && y >= 257 && y <= 286)
		{
			c = 7 + (x - 138) / boxSize;

		}
		else if (x >= 137 && x <= 167 && y >= 285 && y <= 315)
		{
			c = 6;

		}
		else
		{
			c = 12 + (x - 138) / boxSize;

		}
	}
	else if (x >= 314 && x <= 404 && y >= 80 && y <= 257)
	{
		r = 3;
		if (x >= 314 && x <= 344 && y >= 80 && y <= 257)
		{
			c = 5 - (y - 80) / 29;
		}
		else if (x >= 344 && x <= 373 && y >= 80 && y <= 107)
			c = 6;
		else if (x >= 375 && x <= 403 && y >= 80 && y <= 257)
		{
			c = 7 + (y - 80) / 29;
		}
		else
			c = 12 + (y - 80) / 29;
	}
	else if (x >= 404 && x <= 579 && y >= 257 && y <= 343)
	{
		r = 4;
		if (x >= 404 && x <= 579 && y >= 255 && y <= 282)
		{

			c = (x - 404) / boxSize;

		}
		else if (x >= 404 && x <= 580 && y >= 314 && y <= 341)
		{
			c = 12 - (x - 404) / boxSize;
		}
		else if (x >= 549 && x <= 576 && y >= 284 && y <= 310)
		{
			c = 6;

		}
		else
		{
			c = 17 - (x - 404) / boxSize;

		}
	}
	else if (x >= 404 && x <= 579 && y >= 374 && y <= 459)
	{
		r = 5;
		if (x >= 404 && x <= 579 && y >= 372 && y <= 400)
		{

			c = (x - 404) / boxSize;
		}
		else if (x >= 404 && x <= 580 && y >= 431 && y <= 459)
		{
			c = 12 - (x - 404) / boxSize;

		}
		else if (x >= 549 && x <= 576 && y >= 401 && y <= 429)
		{
			c = 6;

		}
		else
		{
			c = 17 - (x - 404) / boxSize;

		}
	}
}
void Game::indexToPos(int& x, int& y, int r, int c)
{
#define offsetx 4;
#define offsety 6;
	if (r == 0)
	{

		if (c >= 0 && c <= 5)
		{
			x = 376 + offsetx;
			y = (c * 29.5) + 461 + offsety;

		}
		else if (c == 6)
		{
			x = 346 + offsetx;
			y = 610 + offsety;
		}
		else if (c >= 7 && c <= 12)
		{
			x = 317 + offsetx;
			y = ((12 - c) * 29.5) + 461 + offsety;
		}
		else
		{
			x = 346 + offsetx;
			y = ((17 - c) * 29.5) + 461 + offsety;
		}
	}
	else if (r == 1)
	{
		if (c >= 0 && c <= 5)
		{
			x = 140 + boxSize * (5 - c)  + offsetx;
			y = 431 +offsety;
		}
		else if (c == 6)
		{
			x = 140 + offsetx;
			y = 401 + offsety;
		}
		else if (c >= 7 && c <= 12)
		{
			x = 140 + boxSize * (c - 7) + offsetx;
			y = 373 + offsety;
		}
		else
		{
			x = 140 + boxSize * (c - 12) + offsetx;
			y = 401 + offsety;

		}
	}
	else if (r == 2)
	{
		if (c>=0&&c<=5)
		{
			x = 141 + boxSize * (5 - c) + offsetx;
			y = 315 + offsety;
		}
		else if (c==6)
		{
			x = 141 + offsetx;
			y = 285 + offsety;

		}
		else if (c>=7&&c<=12)
		{
			x = 141 + boxSize * (c - 7)+offsetx;
			y = 255 + offsety;
		}
		else
		{
			x = 141 + boxSize * (c - 12);
			y = 285 + offsety;

		}
	}
	else if (r == 3)
	{
		if (c >= 0 && c <= 5)
		{
			x = 317 + offsetx;
			y = 80 - boxSize * (c - 5) + offsety;
		}
		else if (c == 6)
		{
			x = 345 + offsetx;
			y = 80 + offsety;

		}
		else if (c >= 7 && c <= 12)
		{
			x = 375 + offsetx;
			y = 80 + boxSize * (c - 7) + offsety;
		}
		else
		{
			x = 345 + offsetx;
			y = 80 + boxSize * (c - 12)+offsety;

		}
	}
	else if (r == 4)
	{
		if (c >= 0 && c <= 5)
		{
			x = 406 + boxSize * c + offsetx;
			y = 255 + offsety;
		}
		else if (c == 6)
		{
			x = 550 + offsetx;
			y = 285 + offsety;

		}
		else if (c >= 7 && c <= 12)
		{
			x = 406 - boxSize * (c - 12) + offsetx;
			y = 315 + offsety;
		}
		else
		{
			x = 406 - boxSize * (c - 17) + offsetx;
			y = 285 + offsety;

		}
	}
	else if (r == 5)
	{
		if (c >= 0 && c <= 5)
		{
			x = 406 + boxSize*c + offsetx;
			y = 373 + offsety;
		}
		else if (c == 6)
		{
			x = 550 + offsetx;
			y = 401 + offsety;

		}
		else if (c >= 7 && c <= 12)
		{
			x = 406 - boxSize * (c - 12) + offsetx;
			y = 431 + offsety;
		}
		else
		{
			x = 406 - boxSize * (c - 17) + offsetx;
			y = 401 + offsety;

		}
	}
}


bool Game::unlockPiece(int& x, int& y, int& r, int& c,string& _pieceID, sf::Vector2i mousePos, Player* _currPlayer, Piece**& checkPieces, bool& unlock,const int& roll)
{
	if (roll <6)
		return false;
	if (mousePos.x >= 253 && mousePos.x <= 465 && mousePos.y >= 642 && mousePos.y <= 692)
	{
		if ( _currPlayer->getPlayerID() != "0")
			return false;
		
		
		for (int i = 0; i < _currPlayer->getPieceCount(); ++i)
		{
			if (checkPieces[i]->isLocked())
			{
				unlock = true;
				checkPieces[i]->setLock(false);

				_pieceID = checkPieces[i]->getPieceID();
				r = stoi(_currPlayer->getPlayerID()), c = 8;
				checkPieces[i]->moveToPos(make_pair(r, c));
				indexToPos(x, y, r, c);
				return true;
			}
		}
	}
	else if (mousePos.x >= 85 && mousePos.x <= 249 && mousePos.y >= 466 && mousePos.y <= 513)
	{
		if (_currPlayer->getPlayerID() != "1")
			return false;
		for (int i = 0; i < _currPlayer->getPieceCount(); ++i)
		{
			if (checkPieces[i]->isLocked())
			{
				unlock = true;
				checkPieces[i]->setLock(false);
				_pieceID = checkPieces[i]->getPieceID();

				r = stoi(_currPlayer->getPlayerID()), c = 8;
				checkPieces[i]->moveToPos(make_pair(r, c));
				indexToPos(x, y, r, c);
				return true;
			}
		}
	}
	else if (mousePos.x >= 85 && mousePos.x <= 249 && mousePos.y >= 195 && mousePos.y <= 251)
	{
		if (_currPlayer->getPlayerID() != "2")
			return false;
		for (int i = 0; i < _currPlayer->getPieceCount(); ++i)
		{
			if (checkPieces[i]->isLocked())
			{
				unlock = true;
				checkPieces[i]->setLock(false);

				_pieceID = checkPieces[i]->getPieceID();

				r = stoi(_currPlayer->getPlayerID()), c = 8;
				checkPieces[i]->moveToPos(make_pair(r, c));
				indexToPos(x, y, r, c);
				return true;
			}
		}
	}
	else if (mousePos.x >= 248 && mousePos.x <= 467 && mousePos.y >= 23 && mousePos.y <= 72)
	{
		if (_currPlayer->getPlayerID() != "3")
			return false;
		for (int i = 0; i < _currPlayer->getPieceCount(); ++i)
		{
			if (checkPieces[i]->isLocked())
			{
				unlock = true;
				checkPieces[i]->setLock(false);

				_pieceID = checkPieces[i]->getPieceID();

				r = stoi(_currPlayer->getPlayerID()), c = 8;
				checkPieces[i]->moveToPos(make_pair(r, c));
				indexToPos(x, y, r, c);
				return true;
			}
		}
	}
	else if (mousePos.x >= 469 && mousePos.x <= 632 && mousePos.y >=196 && mousePos.y <= 247)
	{
		if (_currPlayer->getPlayerID() != "4")
			return false;
		for (int i = 0; i < _currPlayer->getPieceCount(); ++i)
		{
			if (checkPieces[i]->isLocked())
			{
				unlock = true;
				checkPieces[i]->setLock(false);

				_pieceID = checkPieces[i]->getPieceID();

				r = stoi(_currPlayer->getPlayerID()), c = 8;
				checkPieces[i]->moveToPos(make_pair(r, c));
				indexToPos(x, y, r, c);
				return true;
			}
		}
	}
	else if (mousePos.x >= 465 && mousePos.x <= 627 && mousePos.y >= 463 && mousePos.y <= 511)
	{
		if (_currPlayer->getPlayerID() != "5")
			return false;
		for (int i = 0; i < _currPlayer->getPieceCount(); ++i)
		{
			if (checkPieces[i]->isLocked())
			{
				unlock = true;
				checkPieces[i]->setLock(false);

				_pieceID = checkPieces[i]->getPieceID();

				r = stoi(_currPlayer->getPlayerID()), c = 8;
				checkPieces[i]->moveToPos(make_pair(r, c));
				indexToPos(x, y, r, c);
				return true;
			}
		}
	}
	return false;
}

int Game::checkMove(int&x,int&y,int &r , int &c,Board &board,Player *_currPlayer,Piece*&movedPiece,string& _pieceID,bool &unlock,const int&roll)
{
	while (window.isOpen())
	{
		if (!checkLegalMoves(_currPlayer) && roll < 6)	// No legal Moves :)
		{
			if(roll!=0)
				sf::sleep(sf::seconds(1));
			return -1;
			
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					
					if (mousePos.x >= 1007 && mousePos.x <= 1254 && mousePos.y >= 582 && mousePos.y <= 691)
						return -1; //End Turn Clicked :D


					cout << mousePos.x << " " << mousePos.y << endl;
					posToIndex(mousePos.x, mousePos.y, r, c);

					//Checks

					pair <int, int> currPosition = make_pair(r, c);
					Piece** checkPieces = _currPlayer->getPieces();
					
					if (unlockPiece(x,y,r,c,_pieceID,mousePos,_currPlayer,checkPieces,unlock,roll))
						return 1;
					if (_currPlayer->getTeam() != nullptr)
					{
						for (int i = 0; i < teamCount; ++i)
						{
							vector<Player*> checkPlayer = teams[i]->getPlayers();
							for (int j = 0; j < checkPlayer.size(); ++j)
							{
								Piece** pieces = checkPlayer[j]->getPieces();
								int count = checkPlayer[j]->getPieceCount();
								for (int k = 0; k < count; ++k)
								{
									if (pieces[k]->getPiecePos() == currPosition && _currPlayer->getTeam() == checkPlayer[j]->getTeam())
									{
										movedPiece = pieces[k];
										_pieceID = movedPiece->getPieceID();
										return 1;
									}
								}
							}
						}
					}
					for (int i = 0; i < _currPlayer->getPieceCount(); ++i)
					{
						if (checkPieces[i]->getPiecePos() == currPosition)
						{
							movedPiece = checkPieces[i];
							_pieceID = movedPiece->getPieceID();
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}
bool Game::movePiece(int steps,Player* _currPlayer,string pieceID,Board &board,int&x,int&y)
{
	
	int currID = stoi(_currPlayer->getPlayerID());
	int pieceIndex = stoi(pieceID);
	Piece* currPiece = _currPlayer->getPieces()[pieceIndex];
	pair<int,int> currPos = _currPlayer->getPieces()[pieceIndex]->getPiecePos();
	
	

	if (currPos.second > 12 && currPos.second + steps > 18)
		return false;
	else if (currPos.second > 12 && currPos.second + steps == 18)
	{
		currPos.second += steps;
		currPiece->moveToPos(currPos);
		return true;
	}	currPos.second += steps;
		if (currPos.second > 12 && (currPiece->getRoundTrip() == false || (currPos.first != currID && currPos.first - 6 != currID))) //Because currPos.first is not updated yet so it can be more than 5 :)
		{
			++currPos.first;
			currPos.second -= 13;
			if (currPos.first > 5)
				currPos.first -= 6;
			if (!currPiece->getRoundTrip()&&currPos.first!=pieceIndex)
				currPiece->setRoundTrip(true);
		}
		else if (currPos.second > 18)
			return false;
		if (currPos.second > 6&&currPos.first==currID&&currPiece->getRoundTrip()==true&&currPos.second - steps <=12)
			currPos.second += 6;	//To move it inside :)
		
		currPiece->moveToPos(currPos);
		indexToPos(x, y, currPos.first, currPos.second);
		return true;
}

Piece* Game::checkTake(Board& board, Piece* _movedPiece, int _playerCount, int _pieceCount, Player**& players)
{
	Square currSquare = board.getSquare(_movedPiece->getPiecePos());
	if (currSquare.isSafe)
		return nullptr;
	Piece* r{};
	int count = 0;
	pair<int, int> pos = _movedPiece->getPiecePos();
	Player* _currPlayer = _movedPiece->getPlayer();
	Team* _currTeam = _currPlayer->getTeam();
	for (int i = 0; i < _playerCount; ++i)
	{
		if (players[i] == _currPlayer || (players[i]->getTeam() == _currTeam && _currTeam != nullptr))
			continue;
		
			Piece** pieces = players[i]->getPieces();
			for (int j = 0; j < _pieceCount; ++j)
			{
				if (pieces[j]->getPiecePos() == pos)
				{
					if (count > 1)
						return nullptr;
					++count;
					r = pieces[j];
				}
			}
		
	}
	if (r != nullptr)
		cout << r->getPlayer()->getPlayerID() << endl;
	return r;
}
pair<float,float> Game::moveToInitialPos(Piece* _piece)
{
	int pieceIndex = stoi(_piece->getPieceID());
	Player* currPlayer = _piece->getPlayer();
	string currPlayerID = currPlayer->getPlayerID();


	if (currPlayerID == "0")
		return make_pair(286 + (pieceIndex * 41.5), 654);
	else if (currPlayerID == "1")
		return make_pair(97 + (pieceIndex * 41.5), 477);
	else if (currPlayerID == "2")
		return make_pair(98 + (pieceIndex * 41.5), 215);
	else if (currPlayerID == "3")
		return make_pair(286 + (pieceIndex * 41.5), 41);
	else if (currPlayerID == "4")
		return make_pair(477 + (pieceIndex * 41.5), 215);
	else
		return make_pair(477 + (pieceIndex * 41.5), 477);
}
bool Game::pugGai(Piece* _piece)
{
	int pieceInd = stoi(_piece->getPieceID());
	Player* currPlayer = _piece->getPlayer();
	Piece** currPieces = currPlayer->getPieces();
	int pieceCount = currPlayer->getPieceCount();
	currPieces[pieceInd]->setPugGai(true);

	for (int i = 0; i < pieceCount; ++i)
	{
		if (!currPieces[i]->getPugGai())
			return false;
	}
	
	
	//currentPlayer->setPieceCount(pieceCount - 1);
	return true;
}

void Game::saveGame(int teamCount, int playerCount,int pieceCount,int turn,Player** players)
{
	ofstream wtr("data.txt");
	wtr << teamCount <<" "<< playerCount<<" " << pieceCount<<" "<<turn;
	wtr << "\n";

	for (int i = 0; i < playerCount; ++i)
	{
		Piece** pieces = players[i]->getPieces();
		for (int j = 0; j < pieceCount; ++j)
		{
			wtr << pieces[j]->getPiecePos().first<<" "<<pieces[j]->getPiecePos().second <<" "<< pieces[j]->isLocked()<<" " << pieces[j]->getRoundTrip()<<" " << pieces[j]->getPugGai();
			wtr << "\n";
		}
	}
	
}
void Game::loadGame(ifstream &rdr,int &teamCount, int &playerCount, int &pieceCount, int &turn)
{
	rdr >> teamCount  >> playerCount >>  pieceCount >>  turn;
}
void Game::loadPieceValues(ifstream& rdr, int& teamCount, int& playerCount, int& pieceCount, int& turn,Player**&players)
{
	for (int i = 0; i < playerCount; ++i)
	{
		Piece** pieces = players[i]->getPieces();
		for (int j = 0; j < pieceCount; ++j)
		{
			pair<int, int> pos;
			rdr >> pos.first >> pos.second;
			pieces[j]->moveToPos(pos);
			bool isLocked, getRoundTrip, getPugGai;
			rdr >> isLocked >> getRoundTrip >> getPugGai;
			pieces[j]->setLock(isLocked);
			pieces[j]->setRoundTrip(getRoundTrip);
			pieces[j]->setPugGai(getPugGai);

		}
	}
}
void Game::setPosAfterLoad(int& teamCount, int& playerCount, int& pieceCount, int& turn, Player**& players, sf::CircleShape**& pieceShapes)
{
	for (int i = 0; i < playerCount; ++i)
	{
		Piece** pieces = players[i]->getPieces();
		for (int j = 0; j < pieceCount; ++j)
		{
			int x, y;
			if (pieces[j]->isLocked())
			{
				pair<float, float> initialPos = moveToInitialPos(pieces[j]);
				pieceShapes[i][j].setPosition(initialPos.first, initialPos.second);
			}
			else
			{
				pair<int, int> pos = pieces[j]->getPiecePos();
				indexToPos(x, y, pos.first, pos.second);
				if(pieces[j]->getPugGai())
					pieceShapes[i][j].setPosition(352, 400);
				else
					pieceShapes[i][j].setPosition(x, y);
			}
		}
	}
}