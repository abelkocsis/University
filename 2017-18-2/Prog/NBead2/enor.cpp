#include "enor.h"
#include <iostream>

Csalad::Csalad(){
    azon = "";
    befizossz = 0;
    befizsszam = 0;
}

Befiz::Befiz(){
    azon = "";
    ido = "";
    befizmenny = 0;
}

std::istream& operator>>(std::istream& is, Befiz &b){
    is >> b.azon >> b.ido >> b.befizmenny;
    return is;
}

Beolv::Beolv(std::string filename){
    f_.open(filename.c_str());
    if (f_.fail()){
        throw FILE_ERROR;
    }
}

void Beolv::read_(){
    
    if (f_ >> dx_){
        sx_ = norm;
    }
    else {
        sx_ = abnorm;
    }
}

void Beolv::next(){
    end_ = sx_ == abnorm;
    if (sx_ == norm){
        current_.azon = dx_.azon;
        current_.befizsszam = 1;
        current_.befizossz = dx_.befizmenny;
        read_();
        while (sx_ == norm && current_.azon == dx_.azon){
            current_.befizsszam++;
            current_.befizossz += dx_.befizmenny;
            read_();
        }
    }
}