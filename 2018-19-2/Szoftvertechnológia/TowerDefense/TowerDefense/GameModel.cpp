#include "pch.h"
#include "GameModel.h"
#include "sstream"
#include <limits>

GameModel::GameModel()
{
	std::srand(std::time(nullptr));
}


GameModel::~GameModel()
{
}

void GameModel::disconnect()
{
	Network.disconnect();
}

void GameModel::init(int isServer, const char* ip, const char* port)
{
	map.resize(n);
	for (int i = 0; i < n; i++)
	{
		map[i].resize(m);
		for (int j = 0; j < m; j++)
		{
			map[i][j].Status = Free;
			map[i][j].Obj = Empty;
			map[i][j].Whose = nobody;
		}

	}

	

	player1 = Player();
	player2 = Player();
	running = true;


	map[Castle1Position.row][Castle1Position.col].Obj = Castle1;
	map[Castle1Position.row][Castle1Position.col].Whose = p1;
	map[Castle1Position.row][Castle1Position.col].Status = Occupied;
	for (int i = Castle1Position.row - 1; i <= Castle1Position.row + 1; i++)
	{
		for (int j = Castle1Position.col; j <= Castle1Position.col + 1; j++)
		{
			if (!(i == Castle1Position.row && j == Castle1Position.col)) {
				map[i][j].Status = Unobtainable;
			}
		}
	}
	
	map[Castle2Position.row][Castle2Position.col].Obj = Castle2;
	map[Castle2Position.row][Castle2Position.col].Whose = p2;
	map[Castle2Position.row][Castle2Position.col].Status = Occupied;
	for (int i = Castle2Position.row - 1; i <= Castle2Position.row + 1; i++)
	{
		for (int j = Castle2Position.col-1; j <= Castle2Position.col; j++)
		{
			if (!(i == Castle2Position.row && j == Castle2Position.col)) {
				map[i][j].Status = Unobtainable;
			}
		}
	}

	currentPlayer = &player1;
	enemyPlayer = &player2;

	player1.castle_hp = base_castle_hp;
	player2.castle_hp = base_castle_hp;

	if(isServer == 1) 
	{
		Network.init(true, ip, port);
		Network.connect(ip, port);
	}
	if(isServer == 0)
	{
		Network.init(false, ip, port);
		Network.connect(ip, port);
	}
}

/*
0 - pass
1,2,3 - build tower 1,2,3
4,5,6 - train soldier 1,2,3
*/
bool GameModel::round(int moveType, Coordinate coord)
{
	switch (moveType)
	{
	case 0:
		break;
	case 1:
		if (checkTower(coord) || !createTower(1, coord)) return false;
		break;
	case 2:
		if (checkTower(coord) || !createTower(2, coord)) return false;
		break;
	case 3:
		if (checkTower(coord) || !createTower(3, coord)) return false;
		break;
	case 4:
		if (!createSoldier(1, coord)) return false;
		break;
	case 5:
		if (!createSoldier(2, coord)) return false;
		break;
	case 6:
		if (!createSoldier(3, coord)) return false;
		break;
	default:
		break;
	}

	calcRoutes();
	soldiersStep();
	std::cout << "firing";
	towersFire();

	if (checkCastles()) {
		gameOver();
	}
	else {
		player1.money += money_per_round;
		player2.money += money_per_round;


		if (current == p1) current = p2;
		else			   current = p1;

		// Use of currentPlayer is deprecated
		if (currentPlayer == &player1) {
			currentPlayer = &player2;
		}
		else {
			currentPlayer = &player1;
		}
	}


	Network.send_msg(toString());
	//std::cout << "\n\n" << toString() << "\n";

}

void GameModel::checkAnswer()
{
	if (Network.newMessage())
		fromString(Network.receive_msg());
}

void GameModel::soldiersStep()
{
	for (int i = 0; i < player1.soldiers.size(); i++)
	{
		Soldier currS = player1.soldiers[i];
		Coordinate currC = currS.getPos();
		Coordinate nextC = ParentToC2[currC.row][currC.col];
		if (map[nextC.row][nextC.col].Obj == Castle2) {
			player2.hitCastle(currS.getDamage());
		}
		else {
			//auto temp = map[currC.row][currC.col];
			map[currC.row][currC.col] = Field();
			if (abs(Castle1Position.row - currC.row) < 2 && currC.col < 2) 
				map[currC.row][currC.col].Status = Unobtainable;
			if (abs(Castle2Position.row - currC.row) < 2 && currC.col > 22)
				map[currC.row][currC.col].Status = Unobtainable;
			currS.setPos(nextC);
			/*map[nextC.row][nextC.col] = Field();*/
		}
		player1.soldiers[i] = currS;
	}
	for (int i = 0; i < player2.soldiers.size(); i++)
	{
		Soldier currS = player2.soldiers[i];
		Coordinate currC = currS.getPos();
		Coordinate nextC = ParentToC1[currC.row][currC.col];
		if (map[nextC.row][nextC.col].Obj == Castle1) {
			player1.hitCastle(currS.getDamage());
		}
		else {
			//auto temp = map[currC.row][currC.col];
			map[currC.row][currC.col] = Field();
			if (abs(Castle1Position.row - currC.row) < 2 && currC.col < 2)
				map[currC.row][currC.col].Status = Unobtainable;
			if (abs(Castle2Position.row - currC.row) < 2 && currC.col > 22)
				map[currC.row][currC.col].Status = Unobtainable;
			currS.setPos(nextC);
			//map[nextC.row][nextC.col] = temp;
		}
		player2.soldiers[i] = currS;
	}
	for (int i = 0; i < player1.soldiers.size(); i++)
	{
		Soldier currS = player1.soldiers[i];
		Coordinate currC = currS.getPos();
		map[currC.row][currC.col] = Field(Sol,currS.solType,p1);
	}
	for (int i = 0; i < player2.soldiers.size(); i++)
	{
		Soldier currS = player2.soldiers[i];
		Coordinate currC = currS.getPos();
		map[currC.row][currC.col] = Field(Sol, currS.solType, p2);
	}
}

void GameModel::towersFire()
{
	for (auto i = 0; i < player1.towers.size(); ++i) {
		player1.towers[i].fire(player2.soldiers);
	}
	for (auto i = 0; i < player2.towers.size(); ++i) {
		player2.towers[i].fire(player1.soldiers);
	}

	for (auto i = 0; i < player1.soldiers.size(); ++i) {
		if (!player1.soldiers[i].alive) {
			auto sol = &player1.soldiers[i];
			// penz
			player2.money += dead_soldier_money;
			// torol mapbol
			map[player1.soldiers[i].getPos().row][player1.soldiers[i].getPos().col].Obj = Empty;
			map[player1.soldiers[i].getPos().row][player1.soldiers[i].getPos().col].Status = Free;
			map[player1.soldiers[i].getPos().row][player1.soldiers[i].getPos().col].Whose = nobody;

			// vectorbol
			player1.soldiers.erase(player1.soldiers.begin() + i);

			// maybe need destuctor;
		}
	}


	for (auto i = 0; i < player2.soldiers.size(); ++i) {
		if (!player2.soldiers[i].alive) {
			auto sol = &player2.soldiers[i];
			// penz
			player1.money += dead_soldier_money;
			// torol mapbol
			map[player2.soldiers[i].getPos().row][player2.soldiers[i].getPos().col].Obj = Empty;
			map[player2.soldiers[i].getPos().row][player2.soldiers[i].getPos().col].Status = Free;
			map[player2.soldiers[i].getPos().row][player2.soldiers[i].getPos().col].Whose = nobody;

			// vectorbol
			player2.soldiers.erase(player2.soldiers.begin() + i);

			// maybe need destuctor;
		}
	}

}

bool GameModel::createTower(int _level, Coordinate _coord)
{
	O towerLevel;
	int rng = base_tower_range;
	int dmg = base_tower_damage;
	std::cout << "asd";

	switch (_level)
	{
	case 1:
		if (currentPlayer->money < tower1_cost) return false;
		currentPlayer->money -= tower1_cost;
		towerLevel = Tower1;
		break;
	case 2:
		if (currentPlayer->money < tower2_cost) return false;
		currentPlayer->money -= tower2_cost;
		towerLevel = Tower2;
		rng = upgraded_tower_range;
		break;
	case 3:
		if (currentPlayer->money < tower3_cost) return false;
		currentPlayer->money -= tower3_cost;
		towerLevel = Tower3;
		dmg = upgraded_tower_damage;
		break;
	default:
		towerLevel = Tower1;
	}
	W whose;
	if (currentPlayer == &player1)
		whose = p1;
	else
		whose = p2;

	map[_coord.row][_coord.col] = Field(Occupied, towerLevel, whose);
	currentPlayer->towers.push_back(Tower(rng, dmg, _coord));
	//map[_coord.row][ _coord.col] = Field(Occupied,Tower1,p1);
	return true;
}

bool GameModel::createSoldier(int _level, Coordinate _coord)
{
	O soldierLevel;
	int hp = base_soldier_hp;
	int dmg = base_soldier_damage;

	switch (_level)
	{
	case 1:
		if (currentPlayer->money < sol1_cost) return false;
		currentPlayer->money -= sol1_cost;
		soldierLevel = Soldier1;
		break;
	case 2:
		if (currentPlayer->money < sol2_cost) return false;
		currentPlayer->money -= sol2_cost;
		soldierLevel = Soldier2;
		hp = upgraded_soldier_hp;
		break;
	case 3:
		if (currentPlayer->money < sol3_cost) return false;
		currentPlayer->money -= sol3_cost;
		soldierLevel = Soldier3;
		dmg = upgraded_soldier_damage;
		break;
	default:
		if (currentPlayer->money < sol1_cost) return false;
		currentPlayer->money -= sol1_cost;
		soldierLevel = Soldier1;
	}
	W whose;
	_coord.row = 7;
	if (currentPlayer == &player1) {
		whose = p1;
		_coord.col = 1;
	}
	else {
		whose = p2;
		_coord.col = 23;
	}
	currentPlayer->soldiers.push_back(Soldier(soldierLevel, hp, dmg, _coord));
	map[_coord.row][_coord.col] = Field(Sol, soldierLevel, whose);

	return true;
}

bool GameModel::free(int i, int j) {
	return map[i][j].Status == Free || map[i][j].Status == Sol || map[i][j].Status == Unobtainable;
}

void GameModel::calcRoutes() {

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Dij[i][j] = std::numeric_limits<int>::max();
		}
	}

	ParentToC1.clear();
	ParentToC2.clear();
	ParentToC1.resize(n);
	ParentToC2.resize(n);
	for (int i = 0; i < n; i++)
	{
		ParentToC1[i].resize(m);
		ParentToC2[i].resize(m);
		for (int j = 0; j < m; j++)
		{
			ParentToC1[i][j].row = -1;
			ParentToC1[i][j].col = -1;

			ParentToC2[i][j].row = -1;
			ParentToC2[i][j].col = -1;

		}
	}
	Castle = Castle1Position;
	Dij[Castle.row][Castle.col] = 0;
	Q.push_back(Castle);

	while (Q.size() > 0) {
		Coordinate x = Q[0];
		Q.erase(Q.begin());
		S.push_back(x);
		if (x.row - 1 >= 0 && free(x.row - 1, x.col) && Dij[x.row - 1][x.col] > Dij[x.row][x.col] + 1) {
			Dij[x.row - 1][x.col] = Dij[x.row][x.col] + 1;
			ParentToC1[x.row - 1][x.col] = x;
			Coordinate atm(x.row - 1, x.col);
			Q.push_back(atm);
		}
		if (x.row + 1 < n && free(x.row + 1, x.col) && Dij[x.row + 1][x.col] > Dij[x.row][x.col] + 1) {
			Dij[x.row + 1][x.col] = Dij[x.row][x.col] + 1;
			ParentToC1[x.row + 1][x.col] = x;
			Coordinate atm(x.row + 1, x.col);
			Q.push_back(atm);
		}
		if (x.col - 1 >= 0 && free(x.row, x.col - 1) && Dij[x.row][x.col - 1] > Dij[x.row][x.col] + 1) {
			Dij[x.row][x.col - 1] = Dij[x.row][x.col] + 1;
			ParentToC1[x.row][x.col - 1] = x;
			Coordinate atm(x.row, x.col - 1);
			Q.push_back(atm);
		}
		if (x.col + 1 < m && free(x.row, x.col + 1) && Dij[x.row][x.col + 1] > Dij[x.row][x.col] + 1) {
			Dij[x.row][x.col + 1] = Dij[x.row][x.col] + 1;
			ParentToC1[x.row][x.col + 1] = x;
			Coordinate atm(x.row, x.col + 1);
			Q.push_back(atm);
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Dij[i][j] = std::numeric_limits<int>::max();
		}
	}

	Castle = Castle2Position;
	Dij[Castle.row][Castle.col] = 0;
	Q.clear();
	Q.push_back(Castle);
	int num = 0;
	while (Q.size() > 0) {
		//std::cout << num++ << " " << Q[0].row << " " << Q[0].col << "\n";
		Coordinate x = Q[0];
		Q.erase(Q.begin());
		S.push_back(x);
		if (x.row - 1 >= 0 && free(x.row - 1, x.col) && Dij[x.row - 1][x.col] > Dij[x.row][x.col] + 1) {
			Dij[x.row - 1][x.col] = Dij[x.row][x.col] + 1;
			ParentToC2[x.row - 1][x.col] = x;
			Coordinate atm(x.row - 1, x.col);
			Q.push_back(atm);
		}
		if (x.row + 1 < n && free(x.row + 1, x.col) && Dij[x.row + 1][x.col] > Dij[x.row][x.col] + 1) {
			Dij[x.row + 1][x.col] = Dij[x.row][x.col] + 1;
			ParentToC2[x.row + 1][x.col] = x;
			Coordinate atm(x.row + 1, x.col);
			Q.push_back(atm);
		}
		if (x.col - 1 >= 0 && free(x.row, x.col - 1) && Dij[x.row][x.col - 1] > Dij[x.row][x.col] + 1) {
			Dij[x.row][x.col - 1] = Dij[x.row][x.col] + 1;
			ParentToC2[x.row][x.col - 1] = x;
			Coordinate atm(x.row, x.col - 1);
			Q.push_back(atm);
		}
		if (x.col + 1 < m && free(x.row, x.col + 1) && Dij[x.row][x.col + 1] > Dij[x.row][x.col] + 1) {
			Dij[x.row][x.col + 1] = Dij[x.row][x.col] + 1;
			ParentToC2[x.row][x.col + 1] = x;
			Coordinate atm(x.row, x.col + 1);
			Q.push_back(atm);
		}

	}

}


bool GameModel::checkTower(Coordinate _coord)
{
	
	if (map[_coord.row][_coord.col].Status != Free) return true;
	map[_coord.row][_coord.col].Status = Occupied;
	calcRoutes();
	map[_coord.row][_coord.col].Status = Free;

	for (Soldier s : player1.soldiers) {
		if (ParentToC2[s.getPos().row][s.getPos().col].col == -1)
			return true;
	}
	if (ParentToC2[Castle1Position.row][Castle1Position.col+1].col == -1)
		return true;
	if (ParentToC1[Castle2Position.row][Castle2Position.col - 1].col == -1)
		return true;
	for (Soldier s : player2.soldiers) {
		if (ParentToC1[s.getPos().row][s.getPos().col].col == -1)
			return true;
	}
	return false;
}

bool GameModel::checkCastles() {
	if (player1.isdead() || player2.isdead()) {
		return true;
	}
	return false;
}

void GameModel::gameOver() {
	std::cout << "GAME OVER";
	running = false;
}

std::string GameModel::mapToString() {
	
	std::string r;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			r += map[i][j].toString();
		}

	}
	r += "#";
	return r;
}

void GameModel::mapFromString(std::string s) {
	std::istringstream f(s);
	std::string splitted;
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (std::getline(f, splitted, '.'))
				map[i][j] = Field(splitted);
		}

	}
}

// player1#player2#map#current
std::string GameModel::toString()
{
	std::string r = "";
	r = player1.toString() + player2.toString() + mapToString() + std::to_string(current) + "#";
	return r;
}

void GameModel::fromString(std::string& s)
{
	//std::cout << s;
	std::istringstream f(s);
	std::string temp;
	std::getline(f, temp, '#');
	player1 = Player(temp);

	std::getline(f, temp, '#');
	player2 = Player(temp);

	std::getline(f, temp, '#');
	mapFromString(temp);

	std::getline(f, temp, '#');
	current = W(std::stoi(temp));
	if (current == p1)
		currentPlayer = &player1;
	else
		currentPlayer = &player2;

	if (checkCastles())
		gameOver();
}
