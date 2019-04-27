#include "zsak.h"
#include <vector>
#include <iostream>

Zsak Zsak::operator = (const Zsak &honnan){
    if ( elemek == honnan.elemek && eloford == honnan.eloford && menny == honnan.menny){
        return honnan;
    }
    delete [] elemek;
    delete [] eloford;
    menny = honnan.menny;
    try{
        elemek = new int [100];
        eloford = new int [100];
    }
    catch (std::bad_alloc) {
        throw(SikertelenLefoglalas);
    }

    for (unsigned i = 0; i < menny; i++)
    {
        *(elemek+i) = *((honnan.elemek)+i);
    }
    for (unsigned i = 0; i < menny; i++)
    {
        *(eloford+i) = *((honnan.eloford)+i);
    }

    return honnan;
}
void Zsak::Berak(int e, int m){
    if (menny % 100 == 99){
        std::vector<int> v1;
        std::vector<int> v2;
        for(unsigned i = 0; i < menny; i++){
            v1.push_back(*(elemek+i));
            v2.push_back(*(eloford+i));
        }
        delete [] elemek;
        elemek = nullptr;
        delete [] eloford;
        eloford = nullptr;
        int u = menny * 2;
        try{
        elemek = new int [u];
        eloford = new int [u];
        }
        catch (std::bad_alloc) {
        throw(SikertelenLefoglalas);
        }
        for (unsigned i = 0; i < menny/2;){
            *(elemek+i) = v1[i];
            *(eloford+i) = v2[i];
        }
    }
    
    
    if (m < 1) throw HibasMennyiseg; 
    int i = 0;
    while (i < menny && *(elemek+i) < e)
        i++;
    if (i == menny){
        *(elemek+i) = e;
        *(eloford+i) = m;
        menny++;
    }
    else if (*(elemek+i) == e){
        *(eloford+i) += m;
    }
    else{
        for (int j = menny; j > i; j--){
            *(elemek+j) = *(elemek+j-1);
            *(eloford+j) = *(eloford+j-1);
        }
        *(elemek+i) = e;
        *(eloford+i) = m;
        menny++;
    }
}
void Zsak::Kivesz(int e, int m){
    if (menny == 0) throw (UresZsak);
    int i = 0;
    while (i < menny && elemek[i] != e)
        i++;
    if (i == menny) throw (HibasElem);
    if (m > eloford[i]) throw (HibasMennyiseg);
    if (m == eloford[i]){

        for (int j = i; j < menny-1; j++){
            *(elemek+j) = *(elemek+j+1);
            *(elemek+j) = *(elemek+j+1);

        }
    menny--;
    }
    else{
        *(eloford+i) -= m;
    }
}
bool Zsak::Ures(){
    if (menny == 0)
        return true;
    else
        return false;
}
int Zsak::Menny(int e){
    int i = 0;
    while (i < menny && *(elemek+i) != e)
        i++;
    if (i == menny)
        return 0;
    else
        return *(eloford+i);
}
void Zsak::Kiir(){
    std::cout << "A zsak tartalma:\n";
    if (menny == 0)
        std::cout << "A zsak ures.\n\n";
    for (int i = 0; i < menny; i++){
        std::cout << "elem: " << *(elemek+i) << "; elofordulas: " << *(eloford+i) << "\n"; 
    }
}
Zsak Zsak::Kulonbseg(Zsak zs){
    Zsak mego;
    std::vector <int> zselemek = zs.kidobelemek();
    std::vector <int> zseloford = zs.kidobeloford();
    int i = 0, j = 0;
    
    while (i < menny){
        if (j == zselemek.size() || *(elemek+i) < zselemek[j]){
            mego.Berak(*(elemek+i), eloford[i]);
            i++;
        }
        else if (*(elemek+i) == zselemek[j]){
            if (*(eloford+i) > zseloford[j]){
                mego.Berak(*(elemek+i), *(eloford+i)-zseloford[j]);
            }
            i++;
            j++;
        }
        else{
            j++;
        }
    }
    return mego;
    
}
std::vector<int> Zsak::kidobelemek(){
    std::vector <int> e;
    for (int i = 0; i < menny; i++){
        e.push_back(*(elemek+i));
    }
    return e;
}
std::vector<int> Zsak::kidobeloford(){
    std::vector <int> e;
    for (int i = 0; i < menny; i++){
        e.push_back(*(eloford+i));
    }
    return e;
}
Zsak::Zsak(const Zsak& zsak){
    menny = zsak.menny;
    try{
        elemek = new int [100];
        eloford = new int [100];
    }
    catch (std::bad_alloc) {
        throw(SikertelenLefoglalas);
    }

    for (unsigned i = 0; i < menny; i++)
    {
        *(elemek+i) = *(zsak.elemek+i);
    }
    for (unsigned i = 0; i < menny; i++)
    {
        *(eloford+i) = *(zsak.eloford+i);
    }

    return;
}
Zsak::Zsak(){
    menny = 0;
    try{
        elemek = new int [100];
        eloford = new int [100];
    }
    catch (std::bad_alloc) {
        throw(SikertelenLefoglalas);
    }
}
void Zsak::Torol(){
    delete [] elemek;
    elemek = nullptr;
    delete [] eloford;
    eloford = nullptr;
}