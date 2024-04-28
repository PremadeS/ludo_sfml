#include"Square.h"
Square::Square() :isOccupied{ false }, isSafe{ false } {};
Square::Square(pair<int, int> _pos) :position{ _pos }, isOccupied{ false }, isSafe{ false }{}
void Square::occupySquare(pair<int, int> _pos) { isOccupied = true; }
void Square::vacateSquare(pair<int, int> _pos) { isOccupied = false; }