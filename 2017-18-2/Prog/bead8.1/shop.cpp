#include "shop.h"

using namespace std;

Shop::Shop(const string &fname, const string &tname):_foods(fname), _tech(tname)
{

}

Goods* Shop::linSearch(const string &name, vector<Goods*> stock) const
{

    Goods *g;
    bool l = false;
    int i = 0;
    while (!l && i < stock.size()){
        Goods* p = stock[i];
        if (p->name==name){
            l = true;
            g = p;
        }
        i++;
    }
    return l?g:nullptr;
    //for(Goods* p : stock){ // unsigned int i = 0; i<stock.size();  ++i     
    //}
}

Goods* Shop::minSearch(const string &name, vector<Goods*> stock) const
{
    Goods *g;
    bool l = false;
    for(Goods* p : stock){ // unsigned int i = 0; i<stock.size();  ++i
        if ((p->name==name && !l ) || (l && p->name==name && p->price<g->price) ){
            g = p;
            l = true;
        }      
    }
    return l?g:nullptr;
}
