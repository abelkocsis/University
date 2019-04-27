#pragma once

#include <vector>
#include <string>
#include "goods.h"

class Technical{
public:
    std::vector<Goods*> _stock;
public:
    Technical(const std::string &fname);
    ~Technical();
};
