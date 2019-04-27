#include <iostream>
#include "enor.h"

using namespace std;

string Vegrehajt(string file){
    Beolv b(file);
    b.first();
    if (b.end()){
        cout << "Ures fajl!"<<endl;
    }
    Csalad cs;
    Csalad mego;
    bool l = false;
    
    while (!b.end()){
        cs = b.current();
        //cout << cs.azon << " "<< cs.befizossz <<endl;
        if (!l && cs.befizsszam >= 3){
            l = true;
            mego = cs;
        }
        else if (l && cs.befizsszam >= 3 && cs.befizossz < mego.befizossz){
            mego = cs;
        }
        b.next();
    }
    return mego.azon;
}

//#define TEST_MODE
#ifndef TEST_MODE

int main(){
    cout << Vegrehajt("in.txt") << endl;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("fajl megnyitasa error", "[FILEOPEN]"){
    CHECK_THROWS(Beolv b("semmi.txt"));
}

TEST_CASE("intervallum hossza", "t:enor"){
    Beolv b ("test/in1.txt");
    b.first();
    CHECK(b.current().azon=="egy");
    Beolv b2 ("test/in2.txt");
    b2.first();
    b2.next();
    CHECK(b2.current().azon=="ketto");
    Beolv b3 ("test/in4.txt");
    b3.first();
    b3.next();
    b3.next();
    b3.next();
    CHECK(b3.current().azon=="negy");
}

TEST_CASE("felsorolando tetelek szerint", "t:enor"){
    Beolv b5("test/in5.txt");
    b5.first();
    b5.next();
    CHECK(b5.end());
    Beolv b6("test/in6.txt");
    b6.first();
    b6.next();
    b6.next();
    CHECK(b6.end());
    Beolv b7("test/in7.txt");
    b7.first();
    for (int i = 0; i < 7; i++){
        b7.next();
    }
    CHECK(b7.end());

}

TEST_CASE("bejarasra jellemzo tesztesetek", "t:enor"){
    Beolv b7 ("test/in7.txt");
    b7.first();
    CHECK(b7.current().azon=="egy");
    CHECK(b7.current().befizossz == 1);

    b7.next();
    CHECK(b7.current().azon=="ketto");
    CHECK(b7.current().befizossz == 2);

    for (int i = 0; i < 6; i++){
        b7.next();
    }
    CHECK(b7.end());

}

TEST_CASE("minimum helye szerint", "felteteles minmumkivalasztas"){
    CHECK(Vegrehajt("test/in8.txt")=="egy");
    CHECK(Vegrehajt("test/in9.txt")=="hat");
    CHECK(Vegrehajt("test/in10.txt")=="harom");
}

TEST_CASE("feltetels szama szerint", "felteteles minmumkivalasztas"){
    CHECK(Vegrehajt("test/in11.txt")=="harom");
    CHECK(Vegrehajt("test/in12.txt")=="negy");
    CHECK(Vegrehajt("test/in13.txt")=="harom");

}

#endif