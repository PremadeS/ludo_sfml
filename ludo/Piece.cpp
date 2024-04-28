#include"Piece.h"
Piece::Piece() :roundTrip{ false }, locked{ true }, player{ nullptr }, pugGai{ false } {}
Piece::Piece(string _ID, pair<int, int> _pos, Player* _player) : pieceID{ _ID }, piecePos{ _pos }, roundTrip{ false }, locked{ true }, player{ _player }, pugGai{false} {}
void Piece::moveToPos(pair<int,int> _pos){	piecePos = _pos;}
Player* Piece::getPlayer() { return player; }
string Piece::getPieceID() const { return pieceID; }
pair<int, int> Piece::getPiecePos()const { return piecePos; }
bool Piece::getRoundTrip()const { return roundTrip; }
bool Piece::isLocked()const { return locked; }
void Piece::setRoundTrip(bool val) { roundTrip = val; }
void Piece::setLock(bool val) { locked = val; }
void Piece::setPugGai(bool val) { pugGai = val; };
bool Piece::getPugGai() { return pugGai; };

