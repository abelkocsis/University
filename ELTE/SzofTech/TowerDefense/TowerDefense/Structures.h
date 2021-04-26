#pragma once
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int build_range = 4;

const int money_per_round = 10;	//
const int base_tower_range = 2; //
const int base_tower_damage = 5; //
const int upgraded_tower_damage = 10; //
const int upgraded_tower_range = 4; //
const int base_soldier_hp = 40; //
const int base_soldier_damage = 10; //
const int upgraded_soldier_hp = 100; //
const int upgraded_soldier_damage = 20; //
const int base_castle_hp = 300;	//
const int dead_soldier_money = 30; //  

const int sol1_cost = 20;
const int sol2_cost = 50;
const int sol3_cost = 45;

const int tower1_cost = 40;
const int tower2_cost = 85;
const int tower3_cost = 100;

/**Pozíciót tároló struktúra*/
struct Coordinate {
	int row, col;
	
	/**Pozíció létrehozása adott paraméterekkel
	 * @param _x sorkoordináta
	 * @param _y oszlopkoordináta
	*/
	Coordinate(int _x,int _y): row(_x),col(_y){}

	/**Default koordináta létrehozása, -1, -1 értékekkel.*/
	Coordinate(): row(-1), col(-1) {}

	/**Koordináták összehasonlítása
	 * @param other másik koordináta
	 */ 
	bool operator==(const Coordinate& other) const { return row == other.row && col == other.col;  }
};

/**Két koordináta távolságát megadó függvény
 * @param c1 Egyik koordináta
 * @param c2 Másik koordináta
 */ 
double distance(Coordinate c1, Coordinate c2);

/** Mező állapota */
enum S { 
	/** Szabad */
	Free, 
	//* Katona */
	Sol, 
	
	/** Lefoglalt */
	Occupied, 
	
	/** Nem elérhető */ 
	Unobtainable, 
	
	/** Építésre alkalmas */
	Buildable 
};

/** Mezőre építendő objektum típúsa */
enum O { 
	/** Sima torony */
	Tower1, 
	/** Nagy hatótávú torony */
	Tower2, 
	/** Erősebb lövésű torony */
	Tower3, 
	/** Sima katona */
	Soldier1, 
	/** Erősebb HP-jű katona */
	Soldier2, 
	
	/** Erősebb sebzésű katona */
	Soldier3, 
	
	Base, 

	/**Üres*/
	Empty, 
	/** Kastély, egyes játékos*/
	Castle1, 
	/** Kettes játékos*/
	Castle2 };

/** Mezőre épített objektum kihez tartozik */
enum W { 
	/** Egyes játékos */
	p1, 
	/** Kettes játékos */
	p2, 
	/** Senkihez */
	nobody

};


/** Mezőt leíró struktúra */
struct Field {
	/** Default mező létrehozása és üresre állítása*/
	Field() : Status(Free), Obj(Empty), Whose(nobody) {}

	/**
	 * Mező létrehozása bemeneti paraméterekkel
	 * @param s mező státusza
	 * @param o mezzőn megjelenítendő objektum
	 * @param w mezőn szereplő objektum tulajdonosa
	*/
	Field(S s, O o, W w) : Status(s), Obj(o), Whose(w) {}

	/**
	 * Mező létrehozás az őt kódoló szövegből
	 * @param s mezőt kódoló szöveg
	 */ 
	Field(std::string s);

	/**Státusza*/
	S Status;
	/**Mezőn megjelenítendő objektum*/
	O Obj;
	/**Megjelenítendő objektum tulajdonosa*/
	W Whose;

	/**Mező kiírása, segédfüggvény debuggoláshoz*/
	void print() const {
		if(int(Obj)!=7) 
		std::cout << int(Obj)<< " ";
		else 
			std::cout << ". ";

	}

	std::string toString();
	
};
