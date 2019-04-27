#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int n;
    cin>>n;
    int napok[n];
    for (int i=0; i<n;i++)
    {
        cin>>napok[i];
    }
    int hanyat=0;
    int eddig=0;
    while (eddig<7)
    {
        if (napok[hanyat]==1)
        {
            hanyat++;
            eddig++;
        }
        else
        {
            hanyat++;
            eddig=0;
        }
    }
    while (napok [hanyat]==1)
    {hanyat--;}
    cout<<hanyat+2;
    return 0;
}
