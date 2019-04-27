#include <iostream>

using namespace std;

bool Vane (int tomb[], int honnan, int meddig, int mihez)
{
    bool egyik=false, masik=false;
    for (int h=honnan; h<mihez; h++)
    {
        if (tomb[h]>tomb[mihez])
        {
            egyik=true;
        }
    }
    for (int k=mihez+1; k<=meddig; k++)
    {
        if (tomb[k]>tomb[mihez])
        {
            masik=true;
        }
    }
    return egyik&masik;
}

int main()
{
    //cout << "Hello world!" << endl;
    int adatszam;
    cin >>adatszam;
    int adatok [adatszam];
    for (int i=0; i<adatszam; i++)

    {
        cin>>adatok[i];
    }
    //cout<<Vane(adatok, 2, 5, 4);
    int szigetbal, szigetjobb;
    int volgypont=0;
    int maxvolgypont=0;
    int megoldasbal, megoldasjobb;
    int j;
    for (int i=0; i<adatszam; i++)
    {
        volgypont=0;
        if (adatok[i]>0)
        {
            j=0;
            while (adatok[i+j]>0)
            {
                j++;
            }
        }
        szigetbal=i;
        szigetjobb=i+j;
        for (int q=szigetbal+1; q<szigetjobb-1; q++)
        {
            if (Vane(adatok, szigetbal, szigetjobb, q))
            {
                volgypont++;
            }
        }
        if (volgypont>maxvolgypont)
        {
            megoldasbal=szigetbal;
            megoldasjobb=szigetjobb;
        }
    }
 cout <<megoldasbal<<" "<<megoldasjobb<<endl;
    return 0;
}
