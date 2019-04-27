#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    //int c[1000]; //ilyet nem szabad csinálni!!!!!!

    int n;
    cin >> n;
    int szul [n][3];

    for (int i = 0; i<n; i++)
    {
        cin >> szul [i][0] >> szul [i] [1] >> szul [i][2];
    }
    for (int i = 0; i<n; i++)
    {
        if (szul [i][0] > 1999)
        {
            cout << "Volt: " <<i+1<<endl;
            return 0;
        }
        else
            if (szul[i][0]==1999 | szul [i][1]<9)
        {
            cout << "Volt: " <<i+1<<endl;
            return 0;
        }
        else if (szul [i][1]==9 | szul [i][2]<18)
        {
            cout << "Volt: " <<i+1<<endl;
            return 0;
        }
    }
    cout << "Nem volt."<<endl;
    return 0;
}
