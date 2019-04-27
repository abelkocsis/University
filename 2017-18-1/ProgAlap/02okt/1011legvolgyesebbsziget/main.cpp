#include <iostream>

using namespace std;
int Volgypontok (int adatok[], int ball, int jobbb);
bool Volgye (int adatok[], int bal, int jobb, int pont);

int Volgypontok (int adatok[], int ball, int jobbb)
{
    int megoldas=0;
    for (int k=ball+1; k<jobbb; k++)
    {
        if (Volgye(adatok, ball, jobbb, k))
        {
            megoldas++;
        }
    }
    return megoldas;
}

bool Volgye (int adatok[], int bal, int jobb, int pont)
{
    bool jobbrol=false, balrol=false;
    for (int j=bal; j<pont; j++)
    {
        if (adatok[j]>adatok[pont])
        {
            balrol=true;
        }
    }
    for (int j=pont+1; j<=jobb; j++)
    {
        if (adatok[j]>adatok[pont])
        {
            jobbrol=true;
        }
    }
    return (jobbrol&balrol);
}

int main()
{
    //cout << "Hello world!" << endl;
    int adatmenny;
    cin>>adatmenny;
    int adatok[adatmenny];
    for (int i=0; i<adatmenny; i++)
    {
        cin>>adatok[i];
    }
    //cout<<Volgypontok(adatok, 2, 5);
    int i;
    bool voltsziget=false;
    int megoldbal, megoldjobb, eddigmax=1;
    int atmbal, atmjobb;
    int mettol=0, meddig=adatmenny-1;
    while (adatok [mettol]>0)
    {
        mettol++;
    }
    while (adatok [meddig]>0)
    {
        meddig--;
    }
    i=mettol;

    while (i<meddig)
    {
        if (adatok[i]>0)
        {
            atmbal=i;
            while (adatok[i]>0)
            {
                atmjobb=i;
                i++;

            }
            //cout<<Volgypontok(adatok, atmbal, atmjobb)<<endl;
            if (Volgypontok(adatok, atmbal, atmjobb)>=eddigmax)
            {
                eddigmax=Volgypontok(adatok, atmbal, atmjobb);
                //cout<<eddigmax<<endl;
                voltsziget=true;
                megoldbal=atmbal;
                megoldjobb=atmjobb;
            }
        }
        else
        {
            i++;
        }
    }
    if (voltsziget)
    {
        cout<<megoldbal+1<<" "<<megoldjobb+1<<endl;
    }
    else
    {
        cout<<0<<endl;
    }

    return 0;
}
