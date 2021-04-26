#pragma once
#include "Structures.h"
#include "Soldier.h"
#include <vector>

//class Soldier;

class Tower
{
public:
	Tower(int _rng, int _dmg, Coordinate _coord) : range(_rng), damage(_dmg), position(_coord) {}
	Tower() {}
	Tower(std::string s);
	~Tower();

	void fire(std::vector<Soldier>& enemySoldiers);
	std::string toString();
private:
	int range, damage;
	Coordinate position;

};

