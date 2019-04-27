//K�sz�tette:    Gregorics Tibor
//D�tum:         2017.08.08.
//Feladat:       Terep t�pusai, a l�nyek l�t�gat�i (visitor)

#pragma once

#include <string>


class Jatekos;
/*class Moho; //Greenfinch = Moho
class Ovatos; //Sandbug = Ovatos
class Taktskus;*/ // Squelchy = Taktikus
//Sand= ingatlan
//Grass = Szolgaltatas
//Marsh = Szerencse

class Mezo
{
public:
    Mezo(){};
    virtual Mezo* akcio(Jatekos *jatekos)=0;
    /*virtual Mezo* akcioOvatos(Ovatos *ovatos);
    virtual Mezo* akcioTaktikus(Taktikus *taktikus);*/
};


class Ingatlan : public Mezo
{
public:
    Mezo* akcio(Jatekos *jatekos) override;
    int allapot;
    Jatekos *kie;
    /*Mezo* akcioOvatos(Ovatos *ovatos) override;
    Mezo* akcioTaktikus(Taktikus *taktikus) override;*/
    Ingatlan(int all = 0):allapot(all), kie(nullptr){};
private:
    static Ingatlan* _instance;
};


class Szolgaltatas : public Mezo
{
public:
    static Szolgaltatas* Instance(int k);
    Mezo* akcio(Jatekos *jatekos) override;
    int mennyit;
    /*Mezo* akcioOvatos(Ovatos *ovatos) override;
    Mezo* akcioTaktikus(Taktikus *taktikus) override;*/
    Szolgaltatas(int m = 0):mennyit(m){}
private:
    static Szolgaltatas* _instance;
};


class Szerencse : public Mezo
{
public:
    static Szerencse* Instance();
    Mezo* akcio(Jatekos *jatekos) override;
    int mennyit;
    /*Mezo* akcioOvatos(Ovatos *ovatos) override;
    Mezo* akcioTaktikus(Taktikus *taktikus) override;*/
    Szerencse(int m = 0):mennyit(m){};
private:
    static Szerencse* _instance;
};
