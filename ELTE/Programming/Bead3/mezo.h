//K�sz�tette:    Gregorics Tibor
//D�tum:         2017.08.08.
//Feladat:       Terep t�pusai, a l�nyek l�t�gat�i (visitor)

#pragma once

#include <string>

class Jatekos;
class Moho;
class Ovatos;
class Taktikus;
//az osszes void *Mezo volt
class Mezo
{
public:
    virtual void akcioMoho(Moho *moho) = 0;
    virtual void akcioOvatos(Ovatos *ovatos) = 0;
    virtual void akcioTaktikus(Taktikus *taktikus) = 0;
};


class Ingatlan : public Mezo
{
public:
    static Ingatlan* Instance();
    void akcioMoho(Moho *moho) override;
    void akcioOvatos(Ovatos *ovatos) override;
    void akcioTaktikus(Taktikus *taktikus) override;
    void allapottortles(){_allapot = 0;}
    int allapotLeker(){return _allapot;}
    Ingatlan(){
        _allapot = 0;
        kie = nullptr;
    }
private:
    int _allapot;
    Jatekos* kie;
};


class Szerencse : public Mezo
{
public:
    void akcioMoho(Moho *moho) override;
    void akcioOvatos(Ovatos *ovatos) override;
    void akcioTaktikus(Taktikus *taktikus) override;
    Szerencse(int m):Mezo(){
        _mennyi = m;
    }
private:
    int _mennyi;
};


class Szolgaltatas : public Mezo
{
public:
    void akcioMoho(Moho *moho) override;
    void akcioOvatos(Ovatos *ovatos) override;
    void akcioTaktikus(Taktikus *taktikus) override;
    Szolgaltatas(int m):Mezo(){
        _mennyi = m;
    }
private:
    int _mennyi;
};
