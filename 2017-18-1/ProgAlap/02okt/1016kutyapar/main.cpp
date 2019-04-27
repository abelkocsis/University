#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;

    int kutyaszam, szempontszam;
    int adatok [100][100];

    cin >> kutyaszam >> szempontszam;
    int x;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < kutyaszam; j++)
        {
            cin >> x;
        }
    }
    for (int i = 2; i < kutyaszam+2; i++)
    {
        for (int j = 0; j < szempontszam; j++)
        {
            cin >> adatok [i][j];
        }
    }

    int i=2, j=2;
    bool van=false, eddigjo;
    int mitvizsgal;
    int seged;
    int hol1, hol2;
    while (!van && i < kutyaszam+1)
    {

        j=2;

        while (!van && j < kutyaszam + 2)
        {

            mitvizsgal = 0;
            eddigjo=true;
            if (j==i)
            {
                j++;
            }
            if (j >= kutyaszam + 2)
            {
                eddigjo=false;
            }
            while (eddigjo && mitvizsgal < szempontszam)
            {
                if (adatok [i][mitvizsgal] >= adatok [j][mitvizsgal])
                {
                    mitvizsgal++;
                }
                else
                {
                    eddigjo=false;
                }
            }
            if (eddigjo)
            {
                van = true;
                hol1=i;
                hol2=j;
            }
            j++;


        }
        i++;



    }



    //cout <<"hol1: "<<hol1<<"hol2: "<<hol2<<endl;
    if (van)
    {
        cout << "VAN"<<endl;
    }
    else
    {
        cout <<"NINCS"<<endl;
    }


    return 0;
}
