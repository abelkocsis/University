//Készítette:    Gregorics Tibor
//Dátum:         2017.08.08.
//Feladat:       Lények versenye

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "creature.h"
#include "ground.h"

using namespace std;

//Feladat:       Adott nevű szöveges állományból a lényeket tartalmazó tömb és
//               a versenypályát tartralmazó tömb feltöltése
//Bemenõ adatok: string str	- szöveges állomány neve
//Kimenõ adatok: vector<Creature*> &creature  - lények pointereinek tömbje
//               vector<int> &court - versenypálya mezőinek tömbje
//Tevékenység:   szöveges állomány alapján létrehozza a lényeket és a címeiket
//               a lényeket tartalmazó tömbe teszi, továbbá
//               a versenypályát tartralmazó tömböt is feltölti
void create(const string &str, vector<Creature*> &creature, vector<Ground*> &court)
{
    ifstream f(str.c_str());
    if(f.fail()) {
        cout << "Nincs meg a fájl\n";
        exit(1);
    }

   // Lények létrehozása
    int n;
    f >> n;
    creature.resize(n);
    for(int i=0; i<n; ++i){
        char ch;
        string name;
        int power;
        f >> ch >> name >> power;
        switch(ch){
        case 'G' : creature[i] = new Greenfinch(name, power); break;
        case 'B' : creature[i] = new Sandbug(name, power);    break;
        case 'S' : creature[i] = new Squelchy(name, power);   break;
        }
    }

   // Pálya betöltése
    int m;
    f >> m;
    court.resize(m);
    for(int j=0; j<m; ++j) {
        int k;
        f >> k;
        switch(k){
            case 0 : court[j] = Sand::Instance();  break;
            case 1 : court[j] = Grass::Instance(); break;
            case 2 : court[j] = Marsh::Instance(); break;
        }
    }
}

//Feladat:       Verseny lebonyolítása
//Bemenõ adatok: vector<Creature*> &creature  - lények pointereinek tömbje
//               vector<int> &court - versenypálya mezőinek tömbje
//Kimenõ adatok: vector<Creature*> &creature  - lények pointereinek tömbje
//               vector<int> &court - versenypálya mezőinek tömbje
//               vector<string> alive - versenyt túlélő lények neveinek tömbje
//Tevékenység:   minden lényt sorban egymás után végig vezet a pályán (közben a pálya változhat),
//               illetve addig, amíg a lény el nem pusztul.
//               kigyűjti a pályát túlélő lények neveit.
vector<string> race(vector<Creature*> &creature, vector<Ground*> &court)
{
    vector<string> alive(0);
    for(unsigned int i=0; i<creature.size(); ++i){
        for(unsigned j=0; creature[i]->alive() && j<court.size(); ++j){
            creature[i]->transmute(court[j]);
        }
        if (creature[i]->alive()) alive.push_back(creature[i]->name());
    }
    return alive;
}

// Ezzel lehet a manualis es a unit teszt mod kozott valtogatni
//#define NORMAL_MODE
#ifdef NORMAL_MODE


//Feladat:       Verseny rendezése különféle lények számára és a túlélő lények neveinak kigyűjtése
//Bemenõ adatok: szöveges állomány
//Kimenõ adatok: konzolra kiírt lények nevei
//Tevékenység:   A versenyzők és a pálya létrehozása aszöveges állomány alapján
//               majd a verseny szimulálása és az eredmény kiírása
int main()
{
    vector<Creature*> creature;
    vector<Ground*> court;
    create("inp.txt", creature, court );

    // Verseny
    vector<string> alive;
    alive = race(creature, court);
    for(unsigned int i=0; i<alive.size(); ++i) cout << alive[i] << endl;

    // Lények megszüntetése
    for(unsigned int i=0; i<creature.size(); ++i) delete creature[i];

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1", "inp1*.txt") {

    vector<Creature*> creature;
    vector<Ground*> court;
    vector<string> alive;

    create("inp11.txt", creature, court );
    alive = race(creature, court);

    CHECK(alive.size() == 0);

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];

    create("inp12.txt", creature, court );
    alive = race(creature, court);

    CHECK(alive.size() == 1);

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];

    create("inp13.txt", creature, court );
    alive = race(creature, court);

    CHECK(alive.size() == 2);

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];
}

TEST_CASE("2", "inp2*.txt") {

    vector<Creature*> creature;
    vector<Ground*> court;
    vector<string> alive;

    create("inp21.txt", creature, court );
    alive = race(creature, court);

    CHECK(alive[0] == "plash");
    CHECK(alive[1] == "bug");

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];

    create("inp22.txt", creature, court );
    alive = race(creature, court);

    CHECK(alive.size() == 0);

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];
}

TEST_CASE("3", "") {

    vector<Creature*> creature;
    vector<Ground*> court;
    vector<string> alive;

    creature.push_back(new Greenfinch("greenish", 1));
    alive = race(creature, court);

    CHECK(creature[0]->alive() == true);

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];


    creature.clear();
    court.clear();
    creature.push_back(new Greenfinch("greenish", 5));
    court.push_back(Sand::Instance()); court.push_back(Grass::Instance()); court.push_back(Marsh::Instance());
    alive = race(creature, court);

    CHECK(creature[0]->alive() == true);
    CHECK(court[0] == Sand::Instance());
    CHECK(court[1] == Grass::Instance());
    CHECK(court[2] == Grass::Instance());

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];


    creature.clear();
    court.clear();
    creature.push_back(new Sandbug("bug", 5));
    court.push_back(Sand::Instance()); court.push_back(Grass::Instance()); court.push_back(Marsh::Instance());
    alive = race(creature, court);

    CHECK(creature[0]->alive() == true);
    CHECK(court[0] == Sand::Instance());
    CHECK(court[1] == Sand::Instance());
    CHECK(court[2] == Grass::Instance());

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];


    creature.clear();
    court.clear();
    creature.push_back(new Squelchy("plash", 10));
    court.push_back(Sand::Instance()); court.push_back(Grass::Instance()); court.push_back(Marsh::Instance());
    alive = race(creature, court);

    CHECK(creature[0]->alive() == true);
    CHECK(court[0] == Sand::Instance());
    CHECK(court[1] == Marsh::Instance());
    CHECK(court[2] == Marsh::Instance());

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];


    creature.clear();
    court.clear();
    creature.push_back(new Squelchy("plash", 5));
    court.push_back(Sand::Instance()); court.push_back(Grass::Instance()); court.push_back(Marsh::Instance());
    alive = race(creature, court);

    CHECK(creature[0]->alive() == false);
    CHECK(court[0] == Sand::Instance());
    CHECK(court[1] == Grass::Instance());
    CHECK(court[2] == Marsh::Instance());

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];
}

TEST_CASE("4", "") {

    vector<Creature*> creature;
    vector<Ground*> court;
    vector<string> alive;

    creature.push_back(new Sandbug("bug", 1));
    court.push_back(Marsh::Instance()); court.push_back(Grass::Instance());
    alive = race(creature, court);

    CHECK(creature[0]->alive() == false);
    CHECK(court[0] == Grass::Instance());
    CHECK(court[1] == Grass::Instance());

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];


    creature.clear();
    court.clear();
    creature.push_back(new Sandbug("bug", 3));
    court.push_back(Grass::Instance()); court.push_back(Marsh::Instance());
    alive = race(creature, court);

    CHECK(creature[0]->alive() == false);
    CHECK(court[0] == Sand::Instance());
    CHECK(court[1] == Grass::Instance());

    for(int i=0; i<(int)creature.size(); ++i) delete creature[i];

}

#endif // NORMAL_MODE
