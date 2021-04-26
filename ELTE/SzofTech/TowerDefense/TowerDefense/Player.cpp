#include "pch.h"
#include "Player.h"
#include <string>
#include <sstream>

Player::Player()
{
}



Player::~Player()
{
}

void Player::hitCastle(int dmg)
{
	castle_hp -= dmg;

}

// money|castle_hp|towers|soldiers

std::string Player::toString()
{
	std::string r = "";
	r += std::to_string(money) + "|";
	r += std::to_string(castle_hp) + "|";
	for (auto& t : towers) r += t.toString();
	r += "|";
	for (auto& s : soldiers) r += s.toString();
	r += "#";

	return r;
}

Player::Player(std::string s)
{
	std::istringstream f(s);
	std::string temp;
	std::getline(f, temp, '|');
	money = std::stoi(temp);
	std::getline(f, temp, '|');
	castle_hp = std::stoi(temp);
	std::getline(f, temp, '|');

	std::istringstream towerstream(temp);
	while (std::getline(towerstream, temp, '.')) towers.push_back(Tower(temp));

	std::getline(f, temp, '#');
	std::istringstream soldierstream(temp);
	while (std::getline(soldierstream, temp, '.')) soldiers.push_back(Soldier(temp));

}
