#include "enor.h"

Aster::Aster(std::string a, std::string m, int t, int ta){
    azon_ = a;
    megfigyeles_ = m;
    tomeg_ = t;
    tav_ = ta;
}

Aster::Aster(){
    azon_ = "";
    megfigyeles_ = "";
    tomeg_ = 0;
    tav_ = 0;
}

Beolv::Beolv(std::string filename){
    f.open(filename.c_str());
    if (f.fail())
        throw FILEERORR;
}

void const Beolv::next(){
    std::string sor;
    getline(f, sor);
    std::string atms;
    int atmi;
    if (sor != "" && !f.fail()){
        sx = norm;
        std::stringstream ss(sor);
        ss >> atms;
        dx.setAz(atms);
        ss >> atms;
        dx.setMeg(atms);
        ss >> atmi;
        dx.setTav(atmi);
        ss >> atmi;
        dx.setTomeg(atmi);
    }
    else{
        sx = abnorm;
    }
}