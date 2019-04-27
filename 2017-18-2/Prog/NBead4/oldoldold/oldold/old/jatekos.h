//K�sz�tette:    Gregorics Tibor
//D�tum:         2017.08.08.
//Feladat:       L�nyek t�pusai


#pragma once

#include <string>
#include "mezo.h"

class Jatekos
{
private:
    std::string _nev;
    int _penz;
    int _hanyadik;
public:
    Jatekos (const std::string &str, int p = 10000, int hanyadik = 0):_nev(str), _penz(p), _hanyadik(hanyadik){};
    std::string name() const { return _nev; }
    bool jatekban() const { return _penz > 0; }
    void penzValt(int p) { _penz += p; }
    //?
    virtual void akcio(Mezo* &mezo) = 0;

    virtual ~Jatekos () {}
};

class Moho : public Jatekos
{
public:
    Moho(const std::string &str, int p = 10000, int hanyadik = 0):Jatekos(str, p, hanyadik){ }
    void akcio(Mezo* &mezo) override { mezo = mezo->akcio(this); }
};

class Ovatos : public Jatekos
{
public:
    Ovatos(const std::string &str, int p = 10000, int hanyadik = 0):Jatekos(str, p, hanyadik){ }
    void akcio(Mezo* &mezo) override { mezo = mezo->akcio(this); }
};

class Taktikus : public Jatekos
{
public:
    Taktikus(const std::string &str, int p = 10000, int hanyadik = 0):Jatekos(str, p, hanyadik) { }
    void akcio(Mezo* &mezo) override { mezo = mezo->akcio(this); }
};
