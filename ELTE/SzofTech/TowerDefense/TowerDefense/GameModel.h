#pragma once
#include "Player.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "network_interface.h"
const int n = 15;
const int m = 25;


class GameModel
{
public:
	GameModel();
	~GameModel();
	void init(int isServer, const char * ip, const char * port);
	bool round(int moveType, Coordinate coord);
	std::vector<std::vector<::Field> > getMap() { return map; }
	::Field& getField(int row, int col) { return map[row][col]; }
	std::vector<std::vector<::Coordinate> > getParentToC1() { return ParentToC1; }
	std::vector<std::vector<::Coordinate> > getParentToC2() { return ParentToC2; }
	bool running = true;
	W getCurrentPlayer() const { return currentPlayer == &player1 ? p1 : p2;  }
	bool isGameOver() const { return running == false; }
	int getMoney(W player) const { return player == p1 ? player1.money : player2.money; }
	int getCastleHp(W player) const { return player == p1 ? player1.castle_hp : player2.castle_hp;  }
	//Player getPlayer(W player) const { return player == p1 ? player1 : player2;  }

	void fromString(std::string& s);
	void disconnect();
	void checkAnswer();

	std::string toString();
	Player player1, player2;
private:
	char ip[12], port[6];
	int Dij[n][m];
	std::vector<Coordinate> Q;
	std::vector<Coordinate> S;
	std::vector<std::vector<Coordinate>> Szulo;
	std::vector<std::vector<Coordinate>> ParentToC1;
	std::vector<std::vector<Coordinate>> ParentToC2;
	int Prev[n];
	// const int n = 10;

	//std::vector<std::vector<Field>> map; 
	Coordinate Castle;
	Coordinate Castle1Position = Coordinate(7, 0);
	Coordinate Castle2Position = Coordinate(7, 24);

	
	Player* currentPlayer;
	Player* enemyPlayer;

	std::vector<std::vector<Field>> map;
	W current = p1;

	void soldiersStep();
	void towersFire();
	bool createTower(int _level, Coordinate _coord)	;
	bool createSoldier(int _level, Coordinate _coord);
	bool free(int i, int j);
	void calcRoutes();
	bool checkTower(Coordinate _coord);
	bool checkCastles();
	void gameOver();

	std::string mapToString();
	void mapFromString( std::string s);

	network_interface Network;
};
