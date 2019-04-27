#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int mennyi, hatar, melyik=-1, melyikar;
    cin >> mennyi >>hatar;
    melyikar=mennyi+999999;
    int arak [mennyi];
    for (int i =0; i<mennyi; i++)
    {
        cin>>arak[i];
        if (arak[i]>hatar&&arak[i]<melyikar)
        {
            melyik=i;
            melyikar=arak[i];
        }
    }
    if (melyik==-1)
    {
        cout<<"-1";
    }
    else
    {
        cout <<melyik+1<<" "<<melyikar<<endl;
    }
    return 0;
}
