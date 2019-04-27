#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int n;
    cin >>n;
    for (int i=1; i<n/2.0; i++)
    {
        for (int j=i; j<n-j & i<=n-i-j & j<=n-i-j; j++)
        {
            if (i+j>n-i-j)
            {
                cout<<i<<" "<<j<<" "<<n-i-j<<endl;
            }

        }
    }
    return 0;
}
