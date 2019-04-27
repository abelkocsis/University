#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int m1, m2, m3=0, m4=0, y1, y2, y3=0, y4=0, f1, f2, f3=0, f4=0,
     i1, i2, i3=0, i4=0, osszesen1, osszesen2, kivont /*osszeadott*/;
    cin >> m1 >> y1>>f1>>i1>>m2>>y2>>f2>>i2;
    i3=i1+i2;
    if (i3>=12)
    {
        f3=i3/12;
        i3=i3%12;
    }
    f3=f3+f1+f2;
    if (f3>=3)
    {
        y3=f3/3;
        f3 =  f3 % 3;
    }
    y3 = y3 + y1 + y2;
    if (y3>=1760)
    {
        m3=y3/1760;
        y3=y3%1760;
    }
    m3=m3+m1+m2;
    cout<<m3<<" "<<y3<<" "<<f3<<" "<<i3<<endl;
    osszesen1=i1+f1*12+y1*3*12+m1*1760*3*12;
    osszesen2=i2+f2*12+y2*3*12+m2*1760*3*12;
    //osszeadott=osszesen1+osszesen2;
    kivont=osszesen1-osszesen2;
    if (kivont<0)
    {
        cout<<"-";
        kivont*=-1;
    }

    //cout <<kivont<<endl;
    m4=kivont/(1760*3*12);
    kivont=kivont-m4*1760*3*12;
    y4=kivont/(3*12);
    kivont=kivont-y4*3*12;
    f4=kivont/12;
    kivont=kivont-f4*12;
    i4=kivont;
    cout<<m4<<" "<<y4<<" "<<f4<<" "<<i4<<endl;


    return 0;
}
