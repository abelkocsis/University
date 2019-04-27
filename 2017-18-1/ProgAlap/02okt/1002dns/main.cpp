#include <iostream>

using namespace std;

bool Benne (string miben, string mi)

{
    int a=0, b=0, c=0;
    while (miben.length()-a>=mi.length()-b & a<miben.length() & b<mi.length())
    {


    if (miben[a]==mi[b])
    {
        a++;
        b++;
        if (b==mi.length())
        {
            //cout <<a-1;
            return true;
        }
    }
    else
    {
        c++;
        a=c;
        b=0;
    }
    }
    return false;
}

int main()
{
    //string nemtommiez = "Valami";
    //cout<<"Valami"<<nemtommiez.length();


    cout << Benne ("Valamiben", "alafmibe") << endl;
    string dns;
    cin>>dns;

    for(int i=dns.length()-1, i>0, i--)
    {

    }

    return 0;
}
