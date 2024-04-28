#include "Player.h"
Player::Player() :pieceCount{ 0 }, pieces{ nullptr }, team{ nullptr } {}
Player::Player(string _ID,int _count,Team* _team):playerID{_ID},pieceCount{_count},team{_team}
{
	pieces = new Piece*[_count];
	for (int i = 0; i < _count; ++i)
		pieces[i] = new Piece(to_string(i), make_pair(0, 0),this);

}
int Player::getPieceCount() { return pieceCount; }
string Player::getPlayerID()const { return playerID; }
Piece** Player::getPieces()const { return pieces; }
void Player::movePiece(string _pieceID,pair<int,int> _pos)
{
	pieces[49 - _pieceID[1]]->moveToPos(_pos);
}
Team* Player::getTeam() { return team; }
void Player::setPieceCount(int count) { pieceCount = count; }