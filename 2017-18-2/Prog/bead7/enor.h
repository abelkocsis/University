#ifndef ENOR_H
#define ENOR_H
#include <fstream>
#include <iosfwd>
#include <sstream>

class Aster{
    public:
        Aster(std::string a, std::string m, int t, int ta);
        Aster();
        std::string const azonosíto (){return azon_;};
        std::string const datum (){return megfigyeles_;};
        int const tomeg() {return tomeg_;};
        int const tav() {return tav_;};
        void setAz (std::string a){azon_ = a;};
        void setMeg (std::string m) {megfigyeles_ = m;};
        void setTomeg (int t) {tomeg_ = t;};
        void setTav(int t) {tav_ = t;};
    private:
        std::string azon_;
        std::string megfigyeles_;
        int tomeg_;
        int tav_;

};

struct Beolv{
    public:
        Beolv(std::string filename = "");
    
        enum Status {norm, abnorm};
        enum Exceptions {FILEERORR};
    
        void const first(){next();};
        void const next();
        Aster current(){return dx;};
        bool const end(){return sx == abnorm;};

    private:
        Status sx;
        Aster dx;
        std::ifstream f;
};

#endif
