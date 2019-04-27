#include "mezo.h"
#include "jatekos.h"

using namespace std;

/*Ingatlan* Ingatlan::_instance = nullptr;
Ingatlan* Ingatlan::Instance()
{
    if(_instance == nullptr) {
        _instance = new Ingatlan();
    }
    return _instance;
}*/

void Ingatlan::akcioMoho(Moho *moho)
{
    switch(this->_allapot){
        case 0:
        if(moho->penz() > 1000){
            moho->penzFizet(1000);
            moho->addIng(this);
            this->kie = moho;
            this->_allapot = 1;
        }
        break;

        case 1:
        if(this->kie == moho){
            if(moho->penz() > 4000){
            moho->penzFizet(4000);
            this->_allapot = 2;
        }
        }
        else{
            this->kie->penzKap(moho->penzFizet(500));
            //this->kie->penzValt(+500);
        }
        break;

        case 2:
        if (this->kie != moho){
            this->kie->penzKap(moho->penzFizet(2000));
        }
    }
}

void Ingatlan::akcioOvatos(Ovatos *ovatos)
{
    switch(this->_allapot){
        case 0:
        if(ovatos->penz() >= 2000){
            ovatos->penzFizet(1000);
            ovatos->addIng(this);
            this->kie = ovatos;
            this->_allapot = 1;
        }
        break;

        case 1:
        if(this->kie == ovatos){
            if(ovatos->penz() >= 8000){
            ovatos->penzFizet(4000);
            this->_allapot = 2;
        }
        }
        else{
            this->kie->penzKap(ovatos->penzFizet(500));
        }
        break;

        case 2:
        if (this->kie != ovatos){
            this->kie->penzKap(ovatos->penzFizet(2000));
        }
    }
    
}

void Ingatlan::akcioTaktikus(Taktikus *taktikus)
{
    switch(this->_allapot){
        case 0:
        if(taktikus->penz() > 1000 ){
            if (taktikus->_vasarlasilehetoseg % 2 == 0){
                taktikus->penzFizet(1000);
                taktikus->addIng(this);
                this->kie = taktikus;
                this->_allapot = 1;
            }
            taktikus->_vasarlasilehetoseg++;

        }
        break;

        case 1:
        if(this->kie == taktikus){
            if(taktikus->penz() > 4000){
                if (taktikus->_vasarlasilehetoseg % 2 == 0){
                    taktikus->penzFizet(4000);
                    this->_allapot = 2;
                }
                taktikus->_vasarlasilehetoseg++;
        }
        }
        else{
            this->kie->penzKap(taktikus->penzFizet(500));

        }
        break;

        case 2:
        if (this->kie != taktikus){
            this->kie->penzKap(taktikus->penzFizet(2000));
        }
    }
}


/*Szerencse* Szerencse::_instance = nullptr;
Szerencse* Szerencse::Instance()
{
    if(_instance == nullptr) {
        _instance = new Szerencse();
    }
    return _instance;
}*/


void Szerencse::akcioMoho(Moho *moho)
{
    moho->penzKap(this->_mennyi);
    
}

void Szerencse::akcioOvatos(Ovatos *ovatos)
{
    ovatos->penzKap(this->_mennyi);
    
}

void Szerencse::akcioTaktikus(Taktikus *taktikus)
{
    taktikus->penzKap(this->_mennyi);
    
}


/*Szolgaltatas* Szolgaltatas::_instance = nullptr;
Szolgaltatas* Szolgaltatas::Instance()
{
    if(_instance == nullptr) {
        _instance = new Szolgaltatas();
    }
    return _instance;
}*/

void Szolgaltatas::akcioMoho(Moho *moho)
{
    moho->penzFizet(this->_mennyi);
}

void Szolgaltatas::akcioOvatos(Ovatos *ovatos)
{
    ovatos->penzFizet(this->_mennyi);
    
}

void Szolgaltatas::akcioTaktikus(Taktikus *taktikus)
{
    taktikus->penzFizet(this->_mennyi);
   
}

int Jatekos::penzFizet(int p) {
    if (p < _penz){
        _penz -= p;
        return p;
    }
    else{
        int mennyittud = _penz;
        _penz = -1;

        for (int i = 0; i < this->_tulajdon.size(); ++i) {
            this->_tulajdon[i]->allapottortles();
        }
        this->_tulajdon.clear();
        return mennyittud;
    }
}
