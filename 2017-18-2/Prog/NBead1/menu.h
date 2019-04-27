#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "zsak.h"

class Menu{
    public:
        void Run();
    private:
        void UjZsak();
        void ElemBe();
        void ElemKi();
        void ZsakUres();
        void ZsakElemszam();
        void ZsakKulonbseg();
        void ZsakKiir();
        void Masol();
        void Ertekadas();
        void Kilep();
};

#endif