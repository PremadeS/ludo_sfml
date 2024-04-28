#pragma once
#include<iostream>
using namespace std;
class Square {

public:
	std::pair<int, int> position;
	bool isOccupied;
	bool isSafe;
	Square();
	Square(std::pair<int, int> _pos);
	void occupySquare(std::pair<int, int> _pos);
	void vacateSquare(std::pair<int, int> _pos);
};
