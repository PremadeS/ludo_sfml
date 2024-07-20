#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
using namespace std;
class Player;
class Team
{
	string teamName;
	vector<Player*> players;

public:
	Team();
	Team(string _name);
	void addPlayer(Player* _player);
	string getName();
	vector<Player*> getPlayers();

};