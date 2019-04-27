#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int hossz;
    int vagasok;
    cin >> hossz>>vagasok;
    int holvagas[vagasok+2];
    holvagas[0]=0;
    holvagas[vagasok+1]=hossz;
    for (int i = 0; i<vagasok; i++)
    {
        cin >> holvagas[i];
    }
    int minimum=100;
    int mosthol=0;
    int ossz=0;
   for (int i=1; i<vagasok+2; i++)
   {
        if (holvagas[i+1]-holvagas[i-1]<=minimum)
        {
            minimum=holvagas[i+1]-holvagas[i-1];
            mosthol=i;
        }

   }
   cout<<mosthol;

    return 0;
}
