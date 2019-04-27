#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int adatszam;
    cin >>adatszam;
    int adatok[adatszam];
    for (int i=0; i<adatszam; i++)
    {
        cin >>adatok[i];
    }
    int mettol, meddig;
    int j=0;
    while (adatok [j]>0)
    {
        j++;
    }
    mettol=j;
    j=1;
    while (adatok [adatszam-j]>0)
    {
        j++;
    }
    meddig=adatszam-j;

    //
    //cout<<mettol<<" "<<meddig<<endl;
    int mostmax=-1;
    int eddigmax=-1;
    bool sziget;
    bool volt=false;
    for (int i=mettol; i<=meddig; i++)
    {
        sziget=false;
        mostmax=-1;

            while (i<=meddig & adatok[i]>0)
            {
                sziget=true;
                volt=true;
                if (adatok[i]>mostmax)
                {
                    mostmax=adatok[i];

                }
                i++;
            }
        if (sziget)
        {


        if (mostmax>eddigmax)
        {
            eddigmax=mostmax;
        }
        else
        {
            cout<< "0"<<endl;
            return 0;
        }
        }
    }
    if (volt)
    {cout<< "1"<<endl;}

    else
    {
        cout<<"0"<<endl;
    }
    return 0;
}
