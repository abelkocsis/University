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
        cin>>adatok[i];
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
    bool sziget, voltsziget=false;
    int legkisebbszintkul=9001;
    int legnagyobb=0, legkisebb=9001;
    int melyikszamu;

    for (int i= mettol; i<=meddig; i++)
    {
        sziget=false;

        legnagyobb=0;
        legkisebb=9001;

        while (i<=meddig & adatok [i]>0)
        {
            sziget=true;
            voltsziget=true;
            if (adatok[i]>legnagyobb)
            {
                legnagyobb=adatok[i];
            }
            if (adatok[i]<legkisebb)
            {
                legkisebb=adatok[i];
            }
            i++;
        }
        if (sziget)
        {
            if (legnagyobb-legkisebb<legkisebbszintkul)
            {
                legkisebbszintkul=legnagyobb-legkisebb;
                melyikszamu=i;
            }
        }

    }


 if (voltsziget)

 {      int bal=1, jobb=0;
    while (adatok [melyikszamu-bal]>0)
    {
        bal++;
    }
    bal=melyikszamu-bal+1;

     cout<<bal+1<<" "<<melyikszamu<<endl;}
 else
 {
     cout<<"0"<<endl;
 }



    return 0;
}
