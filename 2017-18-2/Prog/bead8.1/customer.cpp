#include "customer.h"
#include <fstream>

using namespace std;

Customer::Customer(const std::string &fname)
{
    fstream f(fname.c_str());
    string name;
    while(f >> name) { _list.push_back(name); }
}

void Customer::purchase(Shop &s)
{
    for(unsigned int i=0; i<_list.size(); ++i){
        Goods* p = s.linSearch(_list[i], s._foods._stock);
        if(p!=nullptr) putInCart(p);
    }
    //Hazi
    for(unsigned int i=0; i<_list.size(); ++i){
        Goods* p = s.linSearch(_list[i], s._tech._stock);
        if(p!=nullptr) putInCart(p);
    }
}

void Customer::putInCart(Goods *p)
{
    _goods.push_back(p);
}

