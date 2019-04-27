//Készítette:    Gregorics Tibor
//Dátum:         2017.08.08.
//Feladat:       Lények versenye

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "jatekos.h"
#include "mezo.h"

using namespace std;

//Feladat:       Adott nevű szöveges állományból a lényeket tartalmazó tömb és
//               a versenypályát tartralmazó tömb feltöltése
//Bemenõ adatok: string str	- szöveges állomány neve
//Kimenõ adatok: vector<Jatekos*> &jatekos  - lények pointereinek tömbje
//               vector<int> &tabla - versenypálya mezőinek tömbje
//Tevékenység:   szöveges állomány alapján létrehozza a lényeket és a címeiket
//               a lényeket tartalmazó tömbe teszi, továbbá
//               a versenypályát tartralmazó tömböt is feltölti
int meret;
int hanyan;
void create(const string &str, vector<Jatekos*> &jatekos, vector<Mezo*> &tabla)
{
    ifstream f(str.c_str());
    if(f.fail()) {
        cout << "Nincs meg a fájl\n";
        exit(1);
    }

    // Pálya betöltése
    f >> meret;
    tabla.resize(meret);
    for(int j=0; j<meret; ++j) {
        int k;
        f >> k;
        switch(k){
            case 0 : tabla[j] = new Ingatlan();  break;
            case 1 : 
                f >> k;
                tabla[j] = new Szolgaltatas(k); 
                break;
            case 2 : 
                f >> k;
                tabla[j] = new Szerencse(k); 
                break;
        }
    }

   // Játékosok létrehozása
    f >> hanyan;
    jatekos.resize(hanyan);
    for(int i=0; i<hanyan; ++i){
        string nev;
        char taktika;
        int penz;
        f >> nev >> taktika;
        switch(taktika){
        case 'M' : jatekos[i] = new Moho(nev, 10000, 0); break;
        case 'O' : jatekos[i] = new Ovatos(nev);    break;
        case 'T' : jatekos[i] = new Taktikus(nev);   break;
        }
    }

   
}

//ezt azert még át kell gondolni

void Jatekos::lep(){
    int m = rand()%6 + 1;
    this->_helyzet = (((this->_helyzet)+m) % meret);
}

//Feladat:       Verseny lebonyolítása
//Bemenõ adatok: vector<Jatekos*> &jatekos  - lények pointereinek tömbje
//               vector<int> &tabla - versenypálya mezőinek tömbje
//Kimenõ adatok: vector<Jatekos*> &jatekos  - lények pointereinek tömbje
//               vector<int> &tabla - versenypálya mezőinek tömbje
//               vector<string> jatekban - versenyt túlélő lények neveinek tömbje
//Tevékenység:   minden lényt sorban egymás után végig vezet a pályán (közben a pálya változhat),
//               illetve addig, amíg a lény el nem pusztul.
//               kigyűjti a pályát túlélő lények neveit.
vector<string> race(vector<Jatekos*> &jatekos, vector<Mezo*> &tabla)
{
    vector<string> allas(0);
    /*for(unsigned int i=0; i<jatekos.size(); ++i){
        for(unsigned j=0; jatekos[i]->jatekban() && j<tabla.size(); ++j){
            
            jatekos[i]->akcio(tabla[j]);
        }
        if (jatekos[i]->jatekban()) jatekban.push_back(jatekos[i]->name());
    }*/



    return allas;
}

// Ezzel lehet a manualis es a unit teszt mod kozott valtogatni
#define NORMAL_MODE
#ifdef NORMAL_MODE


//Feladat:       Verseny rendezése különféle lények számára és a túlélő lények neveinak kigyűjtése
//Bemenõ adatok: szöveges állomány
//Kimenõ adatok: konzolra kiírt lények nevei
//Tevékenység:   A versenyzők és a pálya létrehozása aszöveges állomány alapján
//               majd a verseny szimulálása és az eredmény kiírása
int main()
{
    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;
    create("inp.txt", jatekos, tabla );

    // Verseny
    vector<string> jatekban;
    jatekban = race(jatekos, tabla);
    /*for(unsigned int i=0; i<jatekban.size(); ++i) 
        cout << jatekban[i] << endl;
*/
    // Lények megszüntetése
    for(unsigned int i=0; i<jatekos.size(); ++i) delete jatekos[i];

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1", "inp1*.txt") {

    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;
    vector<string> jatekban;

    create("inp11.txt", jatekos, tabla );
    jatekban = race(jatekos, tabla);

    CHECK(jatekban.size() == 0);

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];

    create("inp12.txt", jatekos, tabla );
    jatekban = race(jatekos, tabla);

    CHECK(jatekban.size() == 1);

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];

    create("inp13.txt", jatekos, tabla );
    jatekban = race(jatekos, tabla);

    CHECK(jatekban.size() == 2);

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];
}

TEST_CASE("2", "inp2*.txt") {

    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;
    vector<string> jatekban;

    create("inp21.txt", jatekos, tabla );
    jatekban = race(jatekos, tabla);

    CHECK(jatekban[0] == "plash");
    CHECK(jatekban[1] == "bug");

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];

    create("inp22.txt", jatekos, tabla );
    jatekban = race(jatekos, tabla);

    CHECK(jatekban.size() == 0);

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];
}

TEST_CASE("3", "") {

    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;
    vector<string> jatekban;

    jatekos.push_back(new Moho("greenish", 1));
    jatekban = race(jatekos, tabla);

    CHECK(jatekos[0]->jatekban() == true);

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];


    jatekos.clear();
    tabla.clear();
    jatekos.push_back(new Moho("greenish", 5));
    tabla.push_back(Ingatlan::Instance()); tabla.push_back(Szolgaltatas::Instance()); tabla.push_back(Szerencse::Instance());
    jatekban = race(jatekos, tabla);

    CHECK(jatekos[0]->jatekban() == true);
    CHECK(tabla[0] == Ingatlan::Instance());
    CHECK(tabla[1] == Szolgaltatas::Instance());
    CHECK(tabla[2] == Szolgaltatas::Instance());

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];


    jatekos.clear();
    tabla.clear();
    jatekos.push_back(new Ovatos("bug", 5));
    tabla.push_back(Ingatlan::Instance()); tabla.push_back(Szolgaltatas::Instance()); tabla.push_back(Szerencse::Instance());
    jatekban = race(jatekos, tabla);

    CHECK(jatekos[0]->jatekban() == true);
    CHECK(tabla[0] == Ingatlan::Instance());
    CHECK(tabla[1] == Ingatlan::Instance());
    CHECK(tabla[2] == Szolgaltatas::Instance());

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];


    jatekos.clear();
    tabla.clear();
    jatekos.push_back(new Taktikus("plash", 10));
    tabla.push_back(Ingatlan::Instance()); tabla.push_back(Szolgaltatas::Instance()); tabla.push_back(Szerencse::Instance());
    jatekban = race(jatekos, tabla);

    CHECK(jatekos[0]->jatekban() == true);
    CHECK(tabla[0] == Ingatlan::Instance());
    CHECK(tabla[1] == Szerencse::Instance());
    CHECK(tabla[2] == Szerencse::Instance());

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];


    jatekos.clear();
    tabla.clear();
    jatekos.push_back(new Taktikus("plash", 5));
    tabla.push_back(Ingatlan::Instance()); tabla.push_back(Szolgaltatas::Instance()); tabla.push_back(Szerencse::Instance());
    jatekban = race(jatekos, tabla);

    CHECK(jatekos[0]->jatekban() == false);
    CHECK(tabla[0] == Ingatlan::Instance());
    CHECK(tabla[1] == Szolgaltatas::Instance());
    CHECK(tabla[2] == Szerencse::Instance());

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];
}

TEST_CASE("4", "") {

    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;
    vector<string> jatekban;

    jatekos.push_back(new Ovatos("bug", 1));
    tabla.push_back(Szerencse::Instance()); tabla.push_back(Szolgaltatas::Instance());
    jatekban = race(jatekos, tabla);

    CHECK(jatekos[0]->jatekban() == false);
    CHECK(tabla[0] == Szolgaltatas::Instance());
    CHECK(tabla[1] == Szolgaltatas::Instance());

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];


    jatekos.clear();
    tabla.clear();
    jatekos.push_back(new Ovatos("bug", 3));
    tabla.push_back(Szolgaltatas::Instance()); tabla.push_back(Szerencse::Instance());
    jatekban = race(jatekos, tabla);

    CHECK(jatekos[0]->jatekban() == false);
    CHECK(tabla[0] == Ingatlan::Instance());
    CHECK(tabla[1] == Szolgaltatas::Instance());

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];

}

#endif // NORMAL_MODE
