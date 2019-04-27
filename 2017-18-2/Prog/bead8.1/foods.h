#pragma once

#include <vector>
#include <string>
#include "goods.h"

class Foods{
public:
    std::vector<Goods*> _stock;
public:
    Foods(const std::string &fname);
    ~Foods();
};
