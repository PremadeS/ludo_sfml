#pragma once
#include "Game.h"
class GUI {
	Game Ludo;
	Board board;
	Player** players;
	sf::RenderWindow &window;
	void makeShapes(sf::CircleShape**& pieceShape, const int playerCount, const int pieceCount);
	void drawPieces(sf::CircleShape**& pieceShape, const int playerCount, const int pieceCount,sf::Sprite**&_characters,int turn);
	int rollDice(sf::Sprite& sBoard, sf::CircleShape**& pieceShape, const int playerCount, const int pieceCount,sf::Sprite**&_characters,int turn);
	bool pugGaiGoti(Game& Ludo,Piece* _piece, sf::CircleShape**& pieceShape);
	void drawCharacters(sf::Sprite**& _characters,int count,int turn);
	void drawTurns(int turn);
	bool sleeper(int n);
	void teamCountSelect(int& teamCount);
public:

	GUI(sf::RenderWindow& _window);
	void welcome();
	void teamSelect(int &teamCount);
	void playerSelect(int &playerCount);
	void pieceSelect(int &pieceCount);
	void start(int teamCount,int playerCount,int pieceCount);
};
