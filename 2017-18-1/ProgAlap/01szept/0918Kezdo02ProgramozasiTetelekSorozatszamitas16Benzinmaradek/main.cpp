#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int k, n, b, l;
    cin >> k >>n>>b>>l;
    int hol[n], mennyit[n];
    for (int i=0; i<n; i++)
    {
        cin>>hol [i]>>mennyit[i];
    }
    b = b - hol[0]*l/100 + mennyit[0];

    for (int i=1; i<n; i++)
    {
        b=b-(hol[i]-hol[i-1])*l/100+mennyit[i];
    }
    b=b-(k-hol[n-1])*l/100;
    cout<<b;


    return 0;
}
