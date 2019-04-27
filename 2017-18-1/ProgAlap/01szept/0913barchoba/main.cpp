#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;


    cout <<"Udvozlom a jatekban! Gondoljon egy 1 es 1000 kozotti egesz szamra!"<<endl;
   // int maradt = 1000;
    int n = 500;
    int valasz;
    int max=1000, min=1;

    while (max>min)
    {


    cout <<"A gondolt szam nagyobb, mint "<<n<<"?"<<endl;
    cin >> valasz;
    if (valasz > 0)
    {
        min = n+1;
    }
    else
    {
        max = n;
    }
    n = (max + min)/2;
    //cout << n <<"     "<<maradt<<endl;
    }




    cout<<"Az On altal gondolt szam a(z) "<<n<<"."<<endl;

    return 0;
}
