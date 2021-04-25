//K�sz�tette:    Gregorics Tibor
//D�tum:         2017.08.08.
//Feladat:       L�nyek t�pusai


#pragma once

#include <string>
#include "mezo.h"
#include <vector>

class Jatekos
{
private:
    std::string _nev;
    int _penz;
    int _holtart;
    std::vector<Ingatlan*> _tulajdon;
public:
    
    Jatekos (const std::string &str):_nev(str), _penz(10000), _holtart(0) {}
    std::string nev() const { return _nev; }
    bool jatekban() const { return _penz > 0; }

    int penz() const {return _penz; }
    int holtart () const {return _holtart;}
    int ingSzam() const{return _tulajdon.size();}
    std::vector<Ingatlan*> Tul () const {return _tulajdon;};
    int penzFizet(int p);
    void penzKap(int p){_penz += p;}
    void lep() ;
    void addIng(Ingatlan* i){_tulajdon.push_back(i);}
    virtual void akcio(Mezo* &mezo) = 0;


    virtual ~Jatekos () {}
};

class Moho : public Jatekos
{
public:
    Moho(const std::string &str):Jatekos(str){ }
    void akcio(Mezo* &mezo) override { mezo->akcioMoho(this); }
}; 

class Ovatos : public Jatekos
{
public:
    Ovatos(const std::string &str):Jatekos(str){ }
    void akcio(Mezo* &mezo) override { mezo->akcioOvatos(this); }
};

class Taktikus : public Jatekos
{
public:
    int _vasarlasilehetoseg;
    Taktikus(const std::string &str):Jatekos(str) {
        _vasarlasilehetoseg = 0;
     }
    void akcio(Mezo* &mezo) override { mezo->akcioTaktikus(this); }
};
