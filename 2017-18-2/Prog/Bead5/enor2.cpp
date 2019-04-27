#include "enor2.h"
#include <sstream>
#include <cstdlib>

Enor2::Enor2(std::string filename){
    f.open(filename.c_str());
    if (f.fail())
        throw FILEERROR;

}

void const Enor2::next(){
    std::string sor;
    getline(f, sor);
    std::stringstream ss;
    if (f.fail() || sor == ""){
        sx = abnorm;
    }
    else{
        sx = norm;
        ss << sor;
        std::string valami;
        ss >> valami;
        dx = valami;
    }
}