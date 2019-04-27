#include "foods.h"

#include <fstream>

using namespace std;

Foods::Foods(const std::string &fname){
    ifstream f(fname.c_str());
    string n;
    int i;
    while(f >> n >> i) {
        Goods* p = new Goods(n,i);
        _stock.push_back(p);
    }
}

Foods::~Foods(){
    for(int i = 0; i<_stock.size(); ++i){
        delete _stock[i];
    }
}
