#include <iostream>
#include "zsak.h"
#include "menu.h"
#include <vector>

using namespace std;

#define TEST_MODE
#ifndef TEST_MODE

int main(){
    Menu m;
    m.Run();
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("konstruktorok", "[Zsak]"){
    Zsak zs;
    CHECK(zs.Ures());
    CHECK(zs.Menny(12) == 0);
    CHECK(zs.Menny(1) == 0);

    Zsak zs1;
    zs1.Berak(1,10);
    zs1.Berak(3,30);
    Zsak zs2(zs1);
    CHECK(zs2.kidobelemek()[0]==1);
    CHECK(zs2.kidobelemek()[1]==3);
    CHECK(zs2.kidobeloford()[0]==10);
    CHECK(zs2.kidobeloford()[1]==30);
    zs2.Berak(2,20);
    CHECK(zs1.Menny(2)==0);
    CHECK(zs2.Menny(2)==20);
    CHECK(zs1.kidobelemek()[1]==3);
    CHECK(zs2.kidobelemek()[1]==2);

}

TEST_CASE("berakas", "[Zsak]"){
    Zsak zs;
    CHECK_THROWS(zs.Berak(2, -8)); //negatív berakásra hiba
    CHECK_THROWS(zs.Berak(3, 0)); // nulla berakásra hiba
    zs.Berak(4,5);
    CHECK(zs.kidobelemek()[0] == 4);
    CHECK(zs.kidobeloford()[0] == 5);
    zs.Berak(1,8);
    zs.Berak(2,7);
    zs.Berak(3,6);
    zs.Berak(5,4);
    zs.Berak(6,3);
    zs.Berak(7,2);
    zs.Berak(8,1);
    CHECK(zs.kidobelemek()[0] == 1);
    CHECK(zs.kidobelemek()[1] == 2);
    CHECK(zs.kidobelemek()[7] == 8);
    CHECK(zs.kidobeloford()[0] == 8);
    CHECK(zs.kidobeloford()[1] == 7);
    CHECK(zs.kidobeloford()[7] == 1);
}
 
TEST_CASE("kivetel", "[Zsak]"){
    Zsak zs;
    CHECK_THROWS(zs.Kivesz(2,2));
    zs.Berak(2,24);
    zs.Berak(1,12);
    zs.Berak(3,33);
    zs.Kivesz(1,7);
    zs.Kivesz(2,24);
    CHECK(zs.kidobelemek()[1] == 3);
    CHECK(zs.kidobeloford()[0] == 5);
    CHECK_THROWS(zs.Kivesz(-2,8));
    CHECK_THROWS(zs.Kivesz(3,35));
}

TEST_CASE("ures, menny", "[Zsak]"){
     Zsak zs;
     CHECK(zs.Ures());
     zs.Berak(2,13);
     zs.Berak(1,24);
     CHECK(zs.Menny(2) == 13);
     CHECK(zs.Menny(1) == 24);
     CHECK(zs.Menny(69) == 0);
}

TEST_CASE("kulonbseg", "[Zsak]"){
    Zsak zs1;
    Zsak zs2;
    zs1.Berak(4,10);
    zs1.Berak(2,20);
    zs1.Berak(1,20);
    
    zs2.Berak(1,10);
    zs2.Berak(3,40);

    Zsak zs3;

    zs3 = zs1.Kulonbseg(zs2);
    
    CHECK(zs3.kidobelemek()[0]==1);
    CHECK(zs3.kidobelemek()[1]==2);
    CHECK(zs3.kidobelemek()[2]==4);
    
    CHECK(zs3.kidobeloford()[0]==10);
    CHECK(zs3.kidobeloford()[1]==20);
    CHECK(zs3.kidobeloford()[2]==10);

    CHECK(zs3.kidobelemek().size()==3);

    zs3.Berak(1,10);
    Zsak zs4;
    zs4 = zs1.Kulonbseg(zs3);
    CHECK(zs4.Ures());

}

TEST_CASE("Ertekadas operator", "[Zsak]"){
    Zsak zs1, zs2, zs3;
    zs1.Berak(1,10);
    zs1.Berak(3,30);
    zs2 = zs1;
    CHECK(zs2.kidobelemek()[0]==1);
    CHECK(zs2.kidobelemek()[1]==3);
    CHECK(zs2.kidobeloford()[0]==10);
    CHECK(zs2.kidobeloford()[1]==30);
    zs1.Berak(2,20);
    CHECK(zs2.Menny(2)==0);
    CHECK(zs1.Menny(2)==20);
    CHECK(zs1.kidobelemek()[1]==2);
    CHECK(zs2.kidobelemek()[1]==3);

    zs3 = zs2 = zs1;
    CHECK(zs2.kidobelemek()[1]==zs3.kidobelemek()[1]);
    zs3.Kivesz(2,10);
    CHECK(zs3.kidobeloford()[1] != zs2.kidobeloford()[1]);
    zs2 = zs1;
    zs1 = zs1;
    CHECK(zs2.kidobelemek()[0] == zs1.kidobelemek()[0]);
    CHECK(zs2.kidobeloford()[1] == zs1.kidobeloford()[1]);

}

#endif