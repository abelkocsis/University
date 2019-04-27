#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int adatmenny;
    cin>>adatmenny;
    int adatok[adatmenny];
    for (int i=0; i<adatmenny; i++)
    {
        cin >>adatok[i];
    }
    int i=0;
    while (adatok[i]>0 & i<adatmenny)
    {
        i++;
    }
    i++;
    int bal, jobb;
    int balosok=0, jobbosok=0;
    while (i<adatmenny)
    {

        if (adatok[i]>0)
        {
            bal=adatok[i];
            i++;
            while (i<adatmenny & adatok[i]>0)
            {
                i++;
            }
            jobb = adatok[i-1];
            //cout<<i<<" "<<bal<<" "<<jobb<<endl;
            if (i<adatmenny)
            {


            if (bal>jobb)
            {
            balosok++;
            }
            else if (jobb>bal)
            {
            jobbosok++;
            }
            }

        }
        else
        {
            i++;
        }

    }
    //jobbosok--;
    //cout<<"balosok "<<balosok<<endl<<"jobbosok "<<jobbosok<<endl;

    if (balosok>jobbosok)
    {
        cout<<"1"<<endl;
    }
    else
    {
        cout <<"0"<<endl;
    }
    return 0;
}
