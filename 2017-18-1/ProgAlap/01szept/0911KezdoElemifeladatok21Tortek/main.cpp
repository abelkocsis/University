#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int sz1, sz2, h1, h2, osz, oh, ksz, kh, szsz, szh, hsz, hh;
    cin >>sz1>>h1>>sz2>>h2;

    osz = sz1 * h2 + sz2 * h1;
    oh = h1 * h2;
    //cout<< osz<<" "<<oh<<endl;


    ksz = sz1 * h2 - sz2 * h1;
    kh = h1 * h2;
    //cout<< osz<<" "<<oh<<endl;



    szsz=sz1*sz2;
    szh=h1*h2;



    hsz= sz1*h2;
    hh=sz2*h1;
 for (int i=30; i>1; i--)
    {
        if (szsz%i==0 & szh%i==0)
        {
            szsz=szsz/i;
            szh=szh/i;
        }
        if (hsz%i==0 & hh%i==0)
        {
            hsz=hsz/i;
            hh=hh/i;
        }
        if (osz%i==0 & oh%i==0)
        {
            osz=osz/i;
            oh=oh/i;
        }
        if (ksz%i==0 & kh%i==0)
        {
            ksz=ksz/i;
            kh=kh/i;
        }
    }

    if (osz==0)
    {
        oh=1;
    }
    if (ksz==0)
    {
        kh=1;
    }
    if (szsz==0)
    {
        szh=1;
    }
    if (hsz==0)
    {
        hh=1;
    }


    cout<< osz<<" "<<oh<<endl;
    cout<< ksz<<" "<<kh<<endl;
    cout<< szsz<<" "<<szh<<endl;
    cout<< hsz<<" "<<hh<<endl;
    return 0;
}
