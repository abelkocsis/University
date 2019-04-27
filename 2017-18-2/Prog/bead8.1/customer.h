#pragma once

#include <vector>
#include <string>
#include "shop.h"

class Customer{
    std::vector<std::string> _list;
    std::vector<Goods*> _goods;
public:
    Customer(const std::string &fname);
    void purchase(Shop &s);
    void putInCart(Goods* g);
    std::vector<Goods*> getGoods(){ return _goods; }
};
