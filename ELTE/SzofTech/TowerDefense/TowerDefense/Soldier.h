#pragma once
#include "Structures.h"

class Soldier
{
public:
	/** Soldier készítése a paraméterek beállításával.
	 * @param _type megjelenítendő objektum típúsa
	 * @param _hp Soldier élete
	 * @param _dmg Soldier sebzésének erőssége
	 * @param _coord Soldier elhelyezkedése
	 */ 

	Soldier(O _type, int _hp, int _dmg, Coordinate _coord): hp(_hp), damage(_dmg), position(_coord), solType(_type) {}
	
	/**
	 * Új katona létrehozása az őt kódoló szövegből.
	 * @param s Katonát kódoló szöveg
	 */ 
	Soldier(std::string s);

	/** Katona létrehozása alapértelmezett értékekkel */
	Soldier() {}
	~Soldier();
	/**Katona sebzése
	 * @param dmg sebzés erőssége
	 */  
	void hit(int dmg);

	/**Katona elhelyezkedését lekérő függvény
	 * @return katona poziciója
	 */ 
	Coordinate getPos() { return position;  };

	/**Katona elhelyezkedését beállító függvény
	 * @param C Új koordináta
	 */ 
	void setPos(Coordinate C){ position = C;};
	/** Katona sebzését adja meg
	 * @return sebzési erősség
	 */ 
	int getDamage(){return damage;};

	/** Katona életét megadó függvény
	 * @return Életerő
	 */  
	int getHp(){return hp;}

	/** Katona elkódolása szöveggé
	 * @return KAtonát kódoló szöveg
	 */ 
	std::string toString();

	/** Megadja, hogy a aktona életben van-?*/
	bool alive = true;

	/** Megadja a katona típúsát*/
	O solType = Soldier1;
	

private:
	int hp;
	int damage;
	Coordinate position;
	//Player player;
};

