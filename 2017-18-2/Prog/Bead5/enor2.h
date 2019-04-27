#ifndef ENOR2_h
#define ENOR2_h
#include <fstream>

class Enor2{
    public:
        Enor2(std::string filename="");
        enum Status{norm, abnorm};
        enum Exception{FILEERROR};
        void const first(){next();};
        std::string const current(){return dx;};
        void const next();
        bool const end(){return sx == abnorm;};
    private:
        Status sx;
        std::string dx;
        std::ifstream f;
};

#endif