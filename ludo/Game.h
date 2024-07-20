#include"Team.h"
#include"Dice.h"
#include "Player.h"
#include<fstream>
#include"Board.h"
#include<SFML/Graphics.hpp>

using namespace std;
class Game {
	Team **teams;
	int teamCount;
	Player* currentPlayer;
	sf::RenderWindow &window;
public:
	Game(sf::RenderWindow&_window);

	Board startGame(int _playerCount,int _pieceCount,int _teamCount,Player **&_players);
	void posToIndex(int x , int y,int &r , int &c );
	void indexToPos(int& x, int& y, int r, int c);
	int checkMove(int&x,int&y,int &r,int&c,Board &board,Player* _currPlayer,Piece*& movedPiece,string&_pieceID,bool &unlock,const int &roll);

	bool movePiece(int steps, Player* _currPlayer, string pieceID,Board &board,int&x,int&y);
	bool checkLegalMoves(Player* _currPlayer);
	bool unlockPiece(int& x, int& y, int& r, int& c,string &_pieceID, sf::Vector2i mousePos, Player* _currPlayer, Piece**& checkPieces,  bool& unlock,const int&roll);
	Piece* checkTake(Board& board, Piece* _movedPiece, int _playerCount, int _pieceCount, Player**& players);
	pair<float,float> moveToInitialPos(Piece* _piece);
	bool pugGai(Piece* _piece);
	void saveGame(int teamCount, int playerCount, int pieceCount,int turn, Player** players);
	void loadGame(ifstream &rdr,int& teamCount, int& playerCount, int& pieceCount, int& turn);
	void loadPieceValues(ifstream& rdr, int& teamCount, int& playerCount, int& pieceCount, int& turn, Player**& players);
	void setPosAfterLoad(int& teamCount, int& playerCount, int& pieceCount, int& turn, Player**& players, sf::CircleShape**& pieceShapes);
};