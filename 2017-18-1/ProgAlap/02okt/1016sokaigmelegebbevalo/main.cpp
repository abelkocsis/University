#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int telepuleszszam, napszam;
    cin >> telepuleszszam >> napszam;
    //int elozoek[telepuleszszam];
    int adatok[telepuleszszam][napszam];
    int mennyi=0;
    int megoldasszam=0;
    int megoldas[1000];

    for (int i = 0; i < telepuleszszam; i++)
    {
        for (int j = 0; j < napszam; j++)
        {
            cin >> adatok [i][j];
        }
    }
    //cout << telepuleszszam/2+telepuleszszam%2<<endl;
    //cout << adatok[2][3];
    for (int i = 1; i < napszam; i++)
    {
        mennyi=0;
        for (int j = 0; j < telepuleszszam; j++)
        {
            if (adatok[j][i]>adatok[j][i-1])
            {
                mennyi++;
               // cout << mennyi<<endl;
            }
        }

        if (mennyi>=telepuleszszam/2)
        {
            megoldas[megoldasszam]=i;
            megoldasszam++;
        }
    }

    cout << megoldasszam<<" ";
    for (int j = 0; j < megoldasszam; j++)
    {


        cout << megoldas[j]+1<<" ";
    }
    cout << endl;

    return 0;
}
