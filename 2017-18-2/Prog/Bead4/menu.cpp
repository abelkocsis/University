#include <iostream>
#include "menu.h"

using namespace std;

int meret;
void Menu::Run(){
    int v;
    do{
        v = MenuPrint();
        switch(v){
            case 1:
                Lefoglal();
                break;
            case 2:
                Berak();
                break;
            case 3:
                Kiolvas();
                break;
            case 4:
                Felszabadit();
                break;
            default:
                Kilep();
                break;

        }
    } while (v != 0);
}

int Menu::MenuPrint(){
    const int n = 4;
    int valasz;
    cout<<"\n****************************************\n";
    cout<<"0. Kilepes\n";
    cout<<"1. Dinamikus tomb lefoglalasa\n";
    cout<<"2. Elem berakasa tombbe\n";
    cout<<"3. Elem kiolvasasa tombbol\n";
    cout<<"4. Dinamikus tomb felszabaditasa\n";
    cout<<"****************************************\n";
    do{
        cout << "Valasztas:";
        cin >> valasz;
    }while(valasz < 0 || valasz > n); 
    return valasz;
}

void Menu::Lefoglal(){
    cout << "Tomb merete: ";
    cin >> meret;
    try {
        dimTomb = new double [meret];
        cout << "Tomb lefoglalasa sikeres.\n";
    }
    catch (bad_alloc) {
        cerr << "\nNincs eleg memoria !\n" << endl;
    }
}

void Menu::Berak(){
    int i, e;
    do {
        cout << "Index: ";
        cin >> i;
    } while (i < 0 || i >= meret);
    cout << "Elem: ";
    cin >> e;
    *(dimTomb+i) = e;
    cout << "Sikeres betetel.\n";
}
void Menu::Kiolvas(){
    int i;
    do {
        cout << "Index: ";
        cin >> i;
    } while (i < 0 || i >= meret);
    cout << "A keresett elem: " << *(dimTomb+i) << "\n";
}
void Menu::Felszabadit(){
    delete [] dimTomb;
    dimTomb = nullptr;
    cout << "Felszabaditas sikeres.\n";
}
void Menu::Kilep(){
    delete [] dimTomb;
    dimTomb = nullptr;
    cout << "Felszabaditas sikeres.\nViszont latasra!\n";
}
