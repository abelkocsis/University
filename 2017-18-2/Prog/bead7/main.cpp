#include <iostream>
#include "enor.h"

using namespace std;

int main(){
    Beolv o ("ast.txt");
    o.first();
    //cout << o.end();
    
    Aster most, elozo = o.current();
    int kulmin = 999999;
    bool l;
    int tom1, tom2;

    while (!o.end()){
        most = elozo = o.current();
        tom1 = tom2 = most.tomeg();
        l = true;
        while (!o.end() && most.azonosíto() == elozo.azonosíto() ){
            if (most.tomeg() >= 10000){
                l = false;
            }
            elozo = most;
            o.next();
            most = o.current();
        }
        
    }
    
}