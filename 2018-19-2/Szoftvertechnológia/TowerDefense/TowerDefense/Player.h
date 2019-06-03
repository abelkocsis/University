#pragma once
#include "Tower.h"
#include "Soldier.h"
#include <string>
#include <vector>
class Player
{
public:
	/** Default Player létrehozás
 	*/ 
	Player();

	/**
 	* Egy Playert hoz létre egy szövegben megkapott adatok alapján.
 	* @param s Playert kódoló szöveg.
 	*/ 
	Player(std::string s);
	~Player();

	/** Az adott játékos kastélyának életéből levon egy bizonyos értéket.
 	* @param dmg Sebzés erőssége
 	*/ 
	void hitCastle(int dmg);

	/** Játékos tornyai.*/
	std::vector<Tower> towers;

	/** Játékos katonái.*/
	std::vector<Soldier> soldiers;

	/** Megvizsgálja, hogy a játékos kastélya elpusztult-e.
	 * @return  halott
	 */ 
	bool isdead (){ return castle_hp <= 0;};

	//*Játékos pénze*/
	int money = 100;
	/*Játékos kastélyának élete*/
	int castle_hp;

	/**
	*	A Player adatatit, mezőit szöveggé alakítja.	
	*/	
	std::string toString();
private:
	std::string name;
};

