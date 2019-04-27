#include "menu.h"
#include <iostream>
#include "zsak.h"
#include <vector>

using namespace std;

vector<Zsak> zsakok;

void Menu::Run(){
    cout << "********************************\nZsak tipus\n\n\n" ;
    int v;
    const int n = 9;
    do {
        cout << "********************************\nValasszon az alabbiak kozul!\n\n";
        cout << "0: Kilepes\n";
        cout << "1: Uj zsak letrehozasa\n";
        cout << "2: Elem berakasa\n";
        cout << "3: Elem kivetele\n";
        cout << "4: Zsak uressegenek vizsgalata\n";
        cout << "5: Adott elem elofordulasanak vizsgalata\n";
        cout << "6: Ket zsak kulonbsege\n";
        cout << "7: Zsak kiiratasa\n";
        cout << "8: Zsak masolasa (masolo konstruktor)\n";
        cout << "9: Korabbi zsak ertekenek egy ujhoz adasa (ertekadas operator)\n";

        do {
            cin >> v;
        } while (v < 0 || v > 9);
        switch (v){
            case 1:
                UjZsak();
                break;
            case 2:
                ElemBe();
                break;
            case 3:
                ElemKi();
                break;
            case 4:
                ZsakUres();
                break;
            case 5:
                ZsakElemszam();
                break;
            case 6:
                ZsakKulonbseg();
                break;
            case 7:
                ZsakKiir();
                break;
            case 8:
                Masol();
                break;
            case 9:
                Ertekadas();
                break;
            default:
                Kilep();
                break;
                
        }

    }while (v != 0);
}
void Menu::UjZsak(){
    Zsak uj;
    zsakok.push_back(uj);
    cout << "Uj zsak letrehozva.\nAz uj zsak sorszama: " << zsakok.size() << "\n";
}
void Menu::ElemBe(){
    if (zsakok.size()==0){
        cout << "Nem lehet zsakba berakni, meg nincs zsak letrehozva.\n\n";
        return;
    }
    int h;
    cout << "Adja meg a zsak sorszamat: ";
    do {
        cin >> h;
    } while (h < 1 || h > zsakok.size());
    cout << "Berakni kivant elem: ";
    int e, m;
    cin >> e;
    cout << "Berakni kivant mennyiseg: ";
    do {
        cin >> m;
    } while (m < 1);
    zsakok[h-1].Berak(e,m);
    cout << "Elem berakasa sikeres.\n";
    zsakok[h-1].Kiir();
    
}
void Menu::ElemKi(){
    if (zsakok.size()==0){
        cout << "Nem lehet zsakbol kivenni, meg nincs zsak letrehozva.\n\n";
        return;
    }
    int h;
    cout << "Adja meg a zsak sorszamat: ";
    do {
        cin >> h;
    } while (h < 1 || h > zsakok.size());
    cout << "Kivenni kivant elem: ";
    int e, m;
    cin >> e;
    cout << "Kivenni kivant mennyiseg: ";
    do {
        cin >> m;
    } while (m < 1);
    zsakok[h-1].Kivesz(e,m);
    cout << "Elem kivetele sikeres.\n";
    zsakok[h-1].Kiir();
}
void Menu::ZsakUres(){
    if (zsakok.size()==0){
        cout << "Meg nincs zsak letrehozva.\n\n";
        return;
    }
    int h;
    cout << "Adja meg a zsak sorszamat: ";
    do {
        cin >> h;
    } while (h < 1 || h > zsakok.size());
    cout << "A zsak ";
    if (!zsakok[h-1].Ures()){
        cout << "nem ";
    }
    cout << "ures.\n"; 
}
void Menu::ZsakElemszam(){
    if (zsakok.size()==0){
        cout << "Meg nincs zsak letrehozva.\n\n";
        return;
    }
    int h, e;
    cout << "Adja meg a zsak sorszamat: ";
    do {
        cin >> h;
    } while (h < 1 || h > zsakok.size());
    cout << "Keresett elem: ";
    cin >> e;
    cout << "Elem elofordulasa: " << zsakok[h-1].Menny(e) << "\n\n";

}
void Menu::ZsakKulonbseg(){
    if (zsakok.size() < 2){
        cout << "Meg nincs eleg zsak letrehozva.\n\n";
        return;
    }
    int h1, h2;
    cout << "Adja meg a kissebitendo zsak sorszamat: ";
    do {
        cin >> h1;
    } while (h1 < 1 || h1 > zsakok.size());
    cout << "Adja meg a kivonando zsak sorszamat: ";
    do {
        cin >> h2;
    } while (h2 < 1 || h2 > zsakok.size());
    zsakok.push_back(zsakok[h1-1].Kulonbseg(zsakok[h2-1]));
    cout << "A kulonbseg vetel sikeres, eredmeny eltarolva a ";
    cout << zsakok.size() << ".-ik zsakban.\n\n";
    zsakok[zsakok.size()-1].Kiir();

}
void Menu::ZsakKiir(){
    if (zsakok.size()==0){
        cout << "Nem lehet zsakot kiiratni, meg nincs zsak letrehozva.\n\n";
        return;
    }
    int h;
    cout << "Adja meg a zsak sorszamat: ";
    do {
        cin >> h;
    } while (h < 1 || h > zsakok.size());
    zsakok[h-1].Kiir();
}
void Menu::Masol(){
    if (zsakok.size()==0){
        cout << "Meg nincs zsak letrehozva.\n\n";
        return;
    }
    int h;
    cout << "Adja meg a masolando zsak sorszamat: ";
    do {
        cin >> h;
    } while (h < 1 || h > zsakok.size());
    Zsak atmzsak(zsakok[h-1]);
    zsakok.push_back(atmzsak);
    cout << "Zsak letrehozva a " << zsakok.size() << ". zsakba.\n";
    zsakok[zsakok.size()-1].Kiir();
}
void Menu::Ertekadas(){
    if (zsakok.size()==0){
        cout << "Nem lehet zsakot ertekul adni, meg nincs zsak letrehozva.\n\n";
        return;
    }
    int h;
    cout << "Adja meg a ertekul adando zsak sorszamat: ";
    do {
        cin >> h;
    } while (h < 1 || h > zsakok.size());

    Zsak atmzs;
    atmzs = zsakok[h-1];
    zsakok.push_back(atmzs);
    cout << "Zsak lemasolva a " << zsakok.size() << ". zsakba.\n";
    zsakok[zsakok.size()-1].Kiir();
    
}
void Menu::Kilep(){
    for (unsigned int i = 0; i < zsakok.size(); i++){
        zsakok[i].Torol();
    }
    if (zsakok.size()>0)
        cout << "Zsakok felszabaditasa sikeres.\nViszont latasra!\n\n";
}