#include "Team.h"
Team::Team(){}
Team::Team(string _name):teamName{_name}{}
string Team::getName() { return teamName; }
void Team::addPlayer(Player* _player) { players.push_back(_player); }
vector<Player*> Team::getPlayers() { return players; }