//K�sz�tette:    Kocsis Ábel
//D�tum:         2018.05.07.


#pragma once

#include <string>

class Jatekos;

class Mezo
{
public:
    virtual Mezo* akcio(Jatekos *jatekos) = 0;
};


class Ingatlan : public Mezo
{
public:
    static Ingatlan* Instance();
    Mezo* akcioMoho(Moho *moho);
    Mezo* akcioOvatos(Ovatos *ovatos);
    Mezo* akcioTaktikus(Taktikus *taktikus);
    
protected:
    Ingatlan(){};
private:
    Jatekos* tulajdonos;
    int allapot;
    static Ingatlan* _instance;
};

//itt csak egy függvény kellene
class Szolgaltatas : public Mezo
{
public:
    static Szolgaltatas* Instance();
    Mezo* akcio(Jatekos *jatekos) override;
protected:
    Szolgaltatas(){}
private:
    static Szolgaltatas* _instance;
};

//itt is csak egy függvény kellene
class Szerencse : public Mezo
{
public:
    static Szerencse* Instance();
    Mezo* akcio(Jatekos *jatekos) override;
protected:
    Szerencse(){}
private:
    static Szerencse* _instance;
};


