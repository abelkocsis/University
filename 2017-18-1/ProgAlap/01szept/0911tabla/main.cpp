#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int v, z;
    cin >> v >> z;
    for (int i=0; i<v; i++)
    {
        for (int j=0; j<z; j++)
        {
            if (i-(v/2.0)>j-z/(2.0))
            {
                //cout<<"a";
                if (i+j+1>(v+z)/2.0)
                {
                    cout<<"a";
                }
                else
                {
                    cout<<"b";
                }
            }
            else
            {
               if (i+j+1>(v+z)/2.0)
                {
                    cout<<"c";
                }
                else
                {
                    cout<<"d";
                }
            }
        }
        cout << endl;
    }
    return 0;
}
