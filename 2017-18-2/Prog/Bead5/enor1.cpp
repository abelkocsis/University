#include "enor1.h"
#include <sstream>
#include <cstdlib>

Enor1::Enor1(std::string filename = ""){
    f_.open(filename.c_str);
    if (f_.fail()){
        throw FILEERROR;
    }
}

void Enor1::next(){
    
}