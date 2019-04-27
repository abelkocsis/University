#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int hanymeres;
    cin>>hanymeres;
    int adatok[hanymeres];
    int a, b, c;
    cin >>a>>b>>c;
    adatok [0]=a;
    adatok[1]=b;
    adatok[2]=c;
    volgyek=0;
    maxvolgyhol=-1;

    for (int i=3; i<hanymeres; i++)
    {
        if (b>0 && b>=a&&b>=c && (b!=a)) ||(b>0 && b>=a&&b>=c && (b!=c))
        {
            volgyek++;
        }
    }

    return 0;
}
