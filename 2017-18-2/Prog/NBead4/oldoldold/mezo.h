#pragma once

#include <string>

class Jatekos;

class Mezo
{
public:
    Mezo(){};
}

class Ingatlan : public Mezo
{
public:
    Ingatlan(int all = 0, k = nullptr) : Mezo(){
        _allapot = all;
        kie = k;
    }
    int getAllapot() const{return _allapot; };
    void setAllapot(int i) {_allapot = i;};
    Jatekos* Tulaj() const {return kie; };
private:
    int _allapot;
    Jatekos* kie;
}


class Szerencse : public Mezo
{
public:
    Szerencse(int m): Mezo(){
        _mennyi = m;
    }
    int getMennyi () const{return _mennyi;};
private: 
    int _mennyi;
}

class Szerencse : public Mezo
{
public:
    Szerencse(int m): Mezo(){
        _mennyi = -1*m;
    }
    int getMennyi () const{return _mennyi;};
private: 
    int _mennyi;
}
