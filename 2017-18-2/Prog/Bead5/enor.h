
#ifndef ENOR_H
#define ENOR_H
#include <fstream>

class Enor{
    public:
        enum Status{abnorm, norm};
        enum Exceptions{FILEERROR};

        Enor(std::string filename = "");
        void first() {next();}
        void next();
        std::string current() const {return dx;}
        bool end() const {return sx==abnorm;}
    private:
        std::string dx;
        Status sx;
        std::ifstream f;
};

#endif