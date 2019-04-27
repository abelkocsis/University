#include <iostream>
//#inculde <string>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int n;
    cin>>n;
    int kor[n];
    string nev[n];
    int ma;

    for (int i=0; i<n; i++)
    {
        cin >>kor[i]>>nev[i];
    }
    cin >> ma;

    int i=0;
    while (i<n&ma-kor[i]<6574)
    {
        i++;
    }
    if (i=n)
    {
        cout<<"NINCS";
    }
    else
    {
        cout<<"VAN";
    }
    return 0;
}
