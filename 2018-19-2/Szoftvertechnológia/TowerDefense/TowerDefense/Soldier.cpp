#include "pch.h"
#include "Soldier.h"
#include <string>
#include <sstream>
Soldier::~Soldier()
{
}

void Soldier::hit(int dmg)
{
	hp -= dmg;
	if (hp <= 0) {
		alive = false;
	}
}

// SolType;alive;hp;damage;posR;posC.
std::string Soldier::toString()
{
	std::string r = "";
	r += std::to_string(solType) + ";";
	r += std::to_string(alive) + ";";
	r += std::to_string(hp) + ";";
	r += std::to_string(damage) + ";";
	r += std::to_string(position.row) + ";";
	r += std::to_string(position.col) + ".";
	
	return r;
}


Soldier::Soldier(std::string s)
{
	std::istringstream f(s);
	std::string temp;
	std::getline(f, temp, ';');
	solType = O(std::stoi(temp));
	std::getline(f, temp, ';');
	alive = std::stoi(temp);
	std::getline(f, temp, ';');
	hp = std::stoi(temp);
	std::getline(f, temp, ';');
	damage = std::stoi(temp);
	std::getline(f, temp, ';');
	position.row = std::stoi(temp);
	std::getline(f, temp, ';');
	position.col = std::stoi(temp);

}