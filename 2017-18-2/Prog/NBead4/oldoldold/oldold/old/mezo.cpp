#include "mezo.h"
#include "jatekos.h"

using namespace std;

Ingatlan* Ingatlan::_instance = nullptr;
Ingatlan* Ingatlan::Instance()
{
    if(_instance == nullptr) {
        _instance = new Ingatlan();
    }
    return _instance;
}

Mezo* Ingatlan::akcioMoho(Moho *moho)
{
    moho->changePower(-2);
    return this;
}

Mezo* Ingatlan::akcioOvatos(Ovatos *ovatos)
{
    ovatos->changePower(3);
    return this;
}

Mezo* Ingatlan::akcioTaktikus(Taktikus *taktikus)
{
    taktikus->changePower(-5);
    return this;
}


Grass* Grass::_instance = nullptr;
Grass* Grass::Instance()
{
    if(_instance == nullptr) {
        _instance = new Grass();
    }
    return _instance;
}

Mezo* Grass::akcioMoho(Moho *moho)
{
    moho->changePower(1);
    return this;
}

Mezo* Grass::akcioOvatos(Ovatos *sandbug)
{
    sandbug->changePower(-2);
    return Ingatlan::Instance();
}

Mezo* Grass::akcioTaktikus(Taktikus *squelchy)
{
    squelchy->changePower(-2);
    return Marsh::Instance();
}


Marsh* Marsh::_instance = nullptr;
Marsh* Marsh::Instance()
{
    if(_instance == nullptr) {
        _instance = new Marsh();
    }
    return _instance;
}

Mezo* Marsh::akcioMoho(Moho *moho)
{
    moho->changePower(-1);
    return Grass::Instance();
}

Mezo* Marsh::akcioOvatos(Ovatos *sandbug)
{
    sandbug->changePower(-4);
    return Grass::Instance();
}

Mezo* Marsh::akcioTaktikus(Taktikus *squelchy)
{
    squelchy->changePower(6);
    return this;
}
