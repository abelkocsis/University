#ifndef  ENOR_H
#define ENOR_H
#include <fstream>
#include <sstream>

class Csalad{
    public:
    Csalad();

    std::string azon;
    int befizossz;
    int befizsszam;
};

class Befiz{
    public:
    Befiz();

    std::string azon;
    std::string ido;
    int befizmenny;

    friend std::istream& operator>>(std::istream& is, Befiz &b);
};

class Beolv{
    public:
    
    Beolv(std::string filename="");

    enum Status {norm, abnorm};
    enum Exceptions {FILE_ERROR};

    void first (){read_(); next();};
    Csalad current () const{return current_;};
    void next();
    bool end () const{return end_;};

    private:
    std::ifstream f_;
    Status sx_;
    Befiz dx_;
    void read_();
    Csalad current_;
    bool end_;

};
#endif