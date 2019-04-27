#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    /*srand(time(NULL));
    double i;
    i=12;
    i= rand()%10;
    if (i>=8)
    {
        i=0;
    }
    else
    {
        i=1;
    }
    cout <<i<<endl;
    return 0;*/
    int n,j;
    cin >>n;
    cin>>j;
    if (n+j==254||n+j==209)
    {
        cout<<"1"<<endl;
    }
    else
    {
        cout<<"0"<<endl;
    }
    return 0;
}
