#ifndef MENU_H
#define MENU_H

class Menu{
    public:
        Menu(){};
        void Run();
    private:
        int MenuPrint();
        void Lefoglal();
        void Berak();
        void Kiolvas();
        void Felszabadit();
        void Kilep();
        double *dimTomb = nullptr;
        int meret;
};

#endif