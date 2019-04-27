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
    std::string _name;
    int _penz;
    int _hanyadik;
    int _helyzet;
public:
    Jatekos (const std::string &str, int p = 10000, int hanyadik = 0):_name(str), _penz(p), _hanyadik(hanyadik){}
    std::string name() const { return _name; }
    bool jatekban() const { return _penz > 0; }
    void penzValt(int p) { _penz += p; }
    bool paros(){ return _hanyadik % 2 == 1;};
    virtual void akcio(Mezo* &mezo);
    void lep();
    std::vector<int> ingatlanok;
    virtual ~Jatekos () {}
};

class Moho : public Jatekos
{
public:
    Moho(const std::string &str, int p = 10000, int hanyadik = 0):Jatekos(str, p, hanyadik){ }
};

class Ovatos : public Jatekos
{
public:
    Ovatos(const std::string &str, int p = 10000, int hanyadik = 0):Jatekos(str, p, hanyadik){ }
};

class Taktikus : public Jatekos
{
public:
    Taktikus(const std::string &str, int p = 10000, int hanyadik = 0):Jatekos(str, p,hanyadik) { }
};
