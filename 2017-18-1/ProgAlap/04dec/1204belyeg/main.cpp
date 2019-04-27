#include <iostream>
#include <vector>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int belyegszam, maxszam;
    cin >> belyegszam >> maxszam;
    int belyegek[belyegszam];
    vector<vector <bool> > Mego (200, vector<bool>(belyegszam+1, false));
    for (int i = 0; i < belyegszam; i++){
        cin >> belyegek[i];
        Mego[1][belyegek[i]] = true;
    }
    int i =2;
    bool vanmeg = true;

    while (vanmeg){
        for (int j: belyegek){

        }
    }


    return 0;
}
