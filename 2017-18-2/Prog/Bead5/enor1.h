#ifndef ENOR1_H
#define ENOR1_H
#include <fstream>


struct Enor1{
    public:
        enum Exeption{FILEERROR};
        enum Status{norm, abnorm};
        Enor1(std::string filename = "");
        void first(){next();};
        void next();
        std::string current()const{return dx_;};
        bool end(){return sx_==abnorm;};
    
    private:
        std::string dx_;
        Status sx_;
        std::ifstream f_;
    
};


#endif