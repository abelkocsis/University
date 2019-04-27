#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int adatszam, tavolsag;
    cin >>adatszam>>tavolsag;
    int adatok[adatszam];
    for (int i=0; i<adatszam; i++)
    {
        cin>>adatok[i];
    }

    int balrol=0;
    int megmennyi=tavolsag+1;
    int j=0;

    while (megmennyi>0 & adatszam>j)
    {
        if (adatok[j]==0)
        {
            megmennyi--;
            j++;
        }
        else
        {
            megmennyi=tavolsag+1;
            balrol++;
            while (adatok[j]==1 && j<adatszam)
            {
                j++;
            }
        }
    }



    cout<< balrol;
    int jobbrol=0;
    megmennyi=tavolsag+1;
     j=1;


while (megmennyi>0 & adatszam-j>=0)
    {
        if (adatok[adatszam-j]==0)
        {
            megmennyi--;
            j++;
        }
        else
        {
            megmennyi=tavolsag+1;
            jobbrol++;
            while (adatok[adatszam-j]==1 && adatszam-j>=0)
            {
                j++;
            }
        }
    }

cout<<" "<<jobbrol<<endl;
    return 0;
}
