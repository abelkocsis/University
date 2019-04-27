#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int n;
    cin >>n;
    int kiesesek [n];
    for (int i=0; i<n; i++)
    {
        cin >> kiesesek[i];

    }
    for (int i= 0; i<n; i++)
    {
        if (kiesesek[i]==1)
        {
            cout << "Az elso kieso: "<<i+1<<endl;
            return 0;
        }
        }
      return 0;
    }


