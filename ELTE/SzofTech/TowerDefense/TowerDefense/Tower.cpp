#include "pch.h"
#include "Tower.h"
#include "Soldier.h"
#include <string>
#include <sstream>

//#include <random>



Tower::~Tower()
{
}

// Select a random enemy unit within range, and call its hit method
// to deal `damage` amount of damage
void Tower::fire(std::vector<Soldier>& enemySoldiers)
{
	std::vector<int> close;
	for (auto i = 0; i < enemySoldiers.size(); ++i) {
		if (distance(position, enemySoldiers[i].getPos()) <= double(range)) {
			close.push_back(i);
		}
		std::cout << distance(position, enemySoldiers[i].getPos());
	}
	std::cout << "*";
	if (close.size() == 0) return;
	int selected = std::rand() % close.size();
	enemySoldiers[ close[selected] ].hit(damage);
}

// range;damage;posRow;posCol
std::string Tower::toString()
{
	std::string r = "";
	r += std::to_string(range) + ";";
	r += std::to_string(damage) + ";";
	r += std::to_string(position.row) + ";";
	r += std::to_string(position.col) + ".";
	return r;
}

Tower::Tower(std::string s)
{
	std::istringstream f(s);
	std::string temp;
	std::getline(f, temp, ';');
	range = std::stoi(temp);
	std::getline(f, temp, ';');
	damage = std::stoi(temp);
	std::getline(f, temp, ';');
	position.row = std::stoi(temp);
	std::getline(f, temp, ';');
	position.col = std::stoi(temp);
	
}