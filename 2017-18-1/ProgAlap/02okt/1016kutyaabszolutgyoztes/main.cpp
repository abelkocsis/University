#include <iostream>

using namespace std;


int main()
{
    //cout << "Hello world!" << endl;
    int kutyaszam, szempontszam;
    int adatok [100][100];
    bool bennvan[100];
    int maxok[100];
    int osszesitett[100];


    for (int i = 0; i < 100; i++)
    {
        bennvan [i] = true;
        maxok [i] = 0;
    }


    //adatok [kutyaszam+2][adatszam]
    cin >> kutyaszam >> szempontszam;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < szempontszam; j++)
        {
            cin >> adatok [i][j];
        }
    }

    int gyoztes, mostosszeg, osszmax = 0;

    for (int i = 2; i < kutyaszam+2; i++)
    {
        mostosszeg = 0;
        for (int j = 0; j < szempontszam; j++)
        {
            cin >> adatok [i][j];
            if (adatok [i][j] > maxok [j])
            {
                maxok [j]=adatok[i][j];
            }
            if (adatok [i][j] < adatok [1][j])
            {
                bennvan [i] = false;
            }
            mostosszeg += adatok [i][j];

        }

        if (bennvan[i] && mostosszeg > osszmax)
        {
            osszmax = mostosszeg;
            gyoztes = i;
        }
    }
    /*cout << "gyoztes: "<<gyoztes<<endl;

    for (int i = 0; i < szempontszam; i++)
    {
        cout << maxok[i]<<" ";
    }*/
    bool van = true;
    int x = 0;
    while (van && x < szempontszam)
    {
        if (adatok[gyoztes][x] >= maxok [x])
        {
            van = false;
        }
        x++;
    }
    if (van)
    {
        cout << "VAN"<<endl;
    }
    else
    {
        cout << "NINCS" << endl;
    }


    return 0;
}
