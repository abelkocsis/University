#include <iostream>

using namespace std;

int mennyilepes;

void H(int n, int A, int B, int C){
    if (n==1)
    {
        cout << n <<" "<< A <<" "<< B <<endl;
        mennyilepes++;
        return;
    }
    else
    {
        H(n-1, A, C, B);
        cout << n <<" " << A << " "<< B << endl;
        mennyilepes++;
        H(n-1, C, B, A);
        return;
    }
}

int main()
{
    //cout << "Hello world!" << endl;
    int n;
    mennyilepes=0;
    cin >> n;
    H(n, 1, 2, 3);
    cout << "lepes: " << mennyilepes << endl;
    return 0;
}
