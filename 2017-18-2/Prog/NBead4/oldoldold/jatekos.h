#pragma once

#include <string>

class Jatekos{
    private:
        std::string _nev;
        int _penz;
        int _helyzet;
        Jatekos(const std::string &str, int p = 100000, int h = 0):_name(str), _penz(p), _helyzet = h{}
    public:
        std::string name() const {return _nev;};
        bool jatekban() const {return penz > 0;};
        void penzValt(int p) {_penz += p; };

        void lepes();
        virtual void action(Mezo* &mezo) = 0;

        virtual ~Jatekos () {};
};

class Taktikus : public Jatekos
{
public:
    Taktikus(const std::string &str, int p = 10000, int h = 0):Jatekos(str, p ,h){}
    void action(Ground* &ground) override;
};

class Moho : public Jatekos
{
public:
    Moho(const std::string &str, int p = 10000, int h = 0):Jatekos(str, p ,h){}
    void action(Ground* &ground) override;
};

class Ovatos : public Jatekos
{
public:
    Ovatos(const std::string &str, int p = 10000, int h = 0):Jatekos(str, p ,h){}
    void action(Ground* &ground) override;
};
