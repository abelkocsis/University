#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int a[10];
    a[0]=5;
    a[9]=69;

    cout << a[0] <<" "<<a[9]<<" "<<endl;

    int b[3] ={1, 2, 3};

    for (int i= 0; i<3; i++)
    {

        cout<<b[i]<<endl;
    }

    string c[4]= {"észak", "dél", "kelet", "nyugat"};
    int d[4][6];
    return 0;
}
