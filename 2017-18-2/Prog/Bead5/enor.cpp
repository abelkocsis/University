#include <cstdlib>
#include <sstream>
#include "enor.h"

Enor::Enor(std::string filename){
    f.open(filename.c_str());
    if (f.fail()){
        throw FILEERROR;
    }
}

void Enor::next(){
    std::string sor;
    getline(f, sor);
    if (!f.fail() && sor != ""){
        sx = norm;
        std::stringstream ss(sor);
        std::string valami1, valami2;
        ss >> valami1;
        ss >> valami2; 
        dx = valami1 + " " + valami2;
    }
    else {
        sx = abnorm;
    }
}