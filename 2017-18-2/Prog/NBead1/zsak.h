#ifndef ZSAK_H
#define ZSAK_H
#include <vector>

class Zsak{
    public:
        Zsak();
        Zsak(const Zsak& zsak);
        enum Hiba{UresZsak, HibasMennyiseg, HibasElem, SikertelenLefoglalas};
        void Berak(int e, int m);
        void Kivesz(int e, int m);
        bool Ures();
        int Menny(int e);
        void Kiir();
        void Torol();
        Zsak Kulonbseg(Zsak zs);
        std::vector<int>kidobelemek();
        std::vector<int>kidobeloford();
        Zsak operator = (const Zsak &honnan);
    private:
        int menny;
        int *elemek;
        int *eloford;
};

#endif