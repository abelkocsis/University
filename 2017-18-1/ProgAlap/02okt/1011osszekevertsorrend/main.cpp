#include <iostream>

using namespace std;

struct Versenyzo
{

    bool vanutana;
    int elotte;
    bool felhasznalva;
};

int main()
{
    //cout << "Hello world!" << endl;

    int hanyember, elsothanyra, masodikathanyra;
    cin>>hanyember>>elsothanyra;
    Versenyzo emberek [hanyember];
    Versenyzo valaki;

    for (int i=0; i<hanyember; i++)
    {

        valaki.vanutana=false;
        valaki.felhasznalva=false;
        valaki.elotte=-2;
        emberek[i]=valaki;

    }
    //emberek[1].utana=18;
    //cout<<emberek[1].utana;
    int x,p;
    int atmeneti[10000];
    for (int i=0; i<elsothanyra; i++)
    {
        cin>>x;

        for (int j=0; j<x; j++)
        {
            cin>>p;
            atmeneti[j]=p-1;
        }
        for (int j=0; j<x; j++)
        {
            if (j==0&&x>1)
            {
                emberek[atmeneti[j]].vanutana=true;
            }
            else if (j==0)
            {
                ;
            }

            else if (j<x-1)
            {
                emberek[atmeneti[j]].vanutana=true;
                emberek[atmeneti[j]].elotte=atmeneti[j-1];
            }
            else
            {
                emberek[atmeneti[j]].elotte=atmeneti[j-1];
            }

           //cout<<emberek[j].utana<<endl;
        }
    }
    /*for (int i = 0; i<hanyember; i++)
    {
        cout<<i+1<<"-edik ember elott all: "<<emberek[i].elotte+1<<endl;
    }*/
    int masodikhanyra;
    cin>>masodikhanyra;
    for (int i=0; i<masodikhanyra; i++)
    {
        cin>>x;

        for (int j=0; j<x; j++)
        {
            cin>>p;
            atmeneti[j]=p-1;
        }
        for (int j=0; j<x; j++)
        {
            if (j==0&&x>1)
            {
                emberek[atmeneti[j]].vanutana=true;
            }
            else if (j==0)
            {
                ;
            }
            else if (j<x-1)
            {
                emberek[atmeneti[j]].vanutana=true;
                emberek[atmeneti[j]].elotte=atmeneti[j-1];
            }
            else
            {
                emberek[atmeneti[j]].elotte=atmeneti[j-1];
            }

           //cout<<emberek[j].utana<<endl;
        }
    }
    /*for (int i = 0; i<hanyember; i++)
    {
        cout<<i+1<<"-edik ember elott all: "<<emberek[i].elotte+1<<endl;
    }
    for (int i = 0; i<hanyember; i++)
    {
        cout<<i+1<<"-edik ember utan all valaki: "<<emberek[i].vanutana<<endl;
    }*/

    int megoldas [hanyember];
    int hanyadiknak=hanyember-1;
    int melyiketbe=-1;
    int megkeres;

    while (hanyadiknak>=0)
    {
        if (melyiketbe==-1)
        {
            megkeres=0;
            while (emberek[megkeres].vanutana || emberek[megkeres].felhasznalva)
            {
                megkeres++;
            }
            melyiketbe=megkeres;
        }
        else
        {
            megoldas[hanyadiknak]=melyiketbe;
            emberek[melyiketbe].felhasznalva=true;
            melyiketbe=emberek[melyiketbe].elotte;
            hanyadiknak--;

        }
    }
    for (int i = 0; i< hanyember; i++)
    {
        cout<<megoldas[i]+1<<" ";
    }





    //cout<<emberek[5].utana<<endl;
    return 0;
}
