//Készítette:    Kocsis Ábel

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>
#include "jatekos.h"
#include "mezo.h"

using namespace std;

int meret;

void Jatekos::lep() {
    int m = rand() % 6 + 1;
    _holtart = (_holtart + m) % (meret );
}

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
            tabla[j] = new Szerencse(k); 
            break;
            case 2 :
            f >> k;
            tabla[j] = new Szolgaltatas(k);
            break;
        }
    }

   // Játékosok létrehozása
    int n;
    f >> n;
    jatekos.resize(n);
    for(int i=0; i<n; ++i){
        char ch;
        string nev;
        f >> nev >> ch;
        switch(ch){
        case 'M' : jatekos[i] = new Moho(nev); break;
        case 'O' : jatekos[i] = new Ovatos(nev);    break;
        case 'T' : jatekos[i] = new Taktikus(nev);   break;
        }
    }

   
}


void race(vector<Jatekos*> &jatekos, vector<Mezo*> &tabla)
{
    unsigned int jatekban = jatekos.size();
    for (int k = 0; jatekban > 1; k++){
        for (int i = 0; i < jatekos.size(); ++i){
            if(jatekos[i]->jatekban()){

                jatekos[i]->lep();
                jatekos[i]->akcio(tabla[jatekos[i]->holtart()]);
                if (!jatekos[i]->jatekban())
                    jatekban--;
            }

        }
        cout << k+1 << ". kor:" << endl;
        for (int j = 0; j < jatekos.size(); ++j) {
            cout << jatekos[j]->nev()<< " " << jatekos[j]->holtart() <<" "<<jatekos[j]->penz() << " " <<jatekos[j]->ingSzam();
            for (int i = 0; i < jatekos[j]->Tul().size(); ++i) {
                if (jatekos[j]->Tul()[i]->allapotLeker() == 2){
                    cout << " " << "haz";
                }
                else{
                    cout << " " << "telek";
                }
            }
            cout << endl;
        }
        cout << endl;
        
    }

    for (int l = 0; l < jatekos.size(); ++l) {
        if ( jatekos[l]->jatekban()){
            cout << "A jatek gyoztese: " << jatekos[l]->nev() << endl;
            return ;
        }
    }


}

//#define NORMAL_MODE
#ifdef NORMAL_MODE


int main()
{
    srand((int)time(0));
    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;
    create("inp.txt", jatekos, tabla );

    race(jatekos, tabla);

    for(unsigned int i=0; i<jatekos.size(); ++i) delete jatekos[i];

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Szolgaltatas", "inp1*.txt") {

    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;

    create("inp1.txt", jatekos, tabla );
    CHECK(jatekos[0]->penz() == 10000);
    jatekos[0]->lep();
    jatekos[0]->akcio(tabla[jatekos[0]->holtart()]);

    CHECK(jatekos[0]->penz() == 8950);
    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];

}
TEST_CASE("Szerencse", "inp2*.txt") {

    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;

    create("inp2.txt", jatekos, tabla );
    jatekos[0]->lep();
    jatekos[0]->akcio(tabla[jatekos[0]->holtart()]);

    CHECK(jatekos[0]->penz() ==11050);

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];
}

TEST_CASE("Ingatlan, moho", "") {
    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;

    create("inp3.txt", jatekos, tabla );
    jatekos[0]->lep();
    jatekos[0]->akcio(tabla[jatekos[0]->holtart()]);

    CHECK(jatekos[0]->penz() == 9000);

    jatekos[0]->lep();
    jatekos[0]->akcio(tabla[jatekos[0]->holtart()]);

    CHECK(jatekos[0]->penz() == 5000);


    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];

}
TEST_CASE("Ingatlan, ovatos", "") {
    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;

    create("inp4.txt", jatekos, tabla );
    jatekos[0]->lep();
    jatekos[0]->akcio(tabla[jatekos[0]->holtart()]);

    CHECK(jatekos[0]->penz() == 9000);

    jatekos[0]->lep();
    jatekos[0]->akcio(tabla[jatekos[0]->holtart()]);

    CHECK(jatekos[0]->penz() == 5000);


    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];

}
TEST_CASE("Ingatlan, taktikus", "") {
    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;

    create("inp5.txt", jatekos, tabla );
    jatekos[0]->lep();
    jatekos[0]->akcio(tabla[jatekos[0]->holtart()]);

    CHECK(jatekos[0]->penz() == 9000);

    jatekos[0]->lep();
    jatekos[0]->akcio(tabla[jatekos[0]->holtart()]);

    CHECK(jatekos[0]->penz() == 9000);


    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];

}
TEST_CASE("Teljes jatek, taktikus", "") {
    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;

    create("inp6.txt", jatekos, tabla );

    for (int k = 0; k < 6; k++){
        for (int i = 0; i < jatekos.size(); ++i){
            if(jatekos[i]->jatekban()){
                jatekos[i]->lep();
                jatekos[i]->akcio(tabla[jatekos[i]->holtart()]);
            }
        }
    }
    CHECK (jatekos[0]->penz() == 25000);
    CHECK (jatekos[1]->penz() == -1);
    CHECK (jatekos[2]->penz() == -1);
    CHECK (jatekos[0]->jatekban());
    CHECK (!jatekos[1]->jatekban());
    CHECK (!jatekos[2]->jatekban());
    CHECK (jatekos[0]->ingSzam() == 1);

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];

};
/*
TEST_CASE("4", "") {

    vector<Jatekos*> jatekos;
    vector<Mezo*> tabla;
    vector<string> jatekban;

    jatekos.push_back(new Ovatos("bug", 1));
    tabla.push_back(Szolgaltatas::Instance()); tabla.push_back(Szerencse::Instance());
    jatekban = race(jatekos, tabla);

    CHECK(jatekos[0]->jatekban() == false);
    CHECK(tabla[0] == Szerencse::Instance());
    CHECK(tabla[1] == Szerencse::Instance());

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];


    jatekos.clear();
    tabla.clear();
    jatekos.push_back(new Ovatos("bug", 3));
    tabla.push_back(Szerencse::Instance()); tabla.push_back(Szolgaltatas::Instance());
    jatekban = race(jatekos, tabla);

    CHECK(jatekos[0]->jatekban() == false);
    CHECK(tabla[0] == Ingatlan::Instance());
    CHECK(tabla[1] == Szerencse::Instance());

    for(int i=0; i<(int)jatekos.size(); ++i) delete jatekos[i];

}*/

#endif 
