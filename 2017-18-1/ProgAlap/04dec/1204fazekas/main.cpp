 #include <iostream>
 #include <vector>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    int targyszam, kap;
    cin >> targyszam >> kap;
    int egi [200];
    for (int i = 0; i < targyszam; i++){
        cin >> egi[i];
    }
    vector<int> DP (targyszam, -1);
    int mennyi, mini, belsomax;
    mini = 99999;

    for (int i = 0; i < targyszam; i++){

        for (int j = 1; j <= kap; j++){
            if (i-j >= 0)
                mennyi = DP[i-j];
            else
                mennyi = 0;
            belsomax = 0;
            for (int l = i-j+1; l <= i; l++){
                if (egi[l] > belsomax)
                    belsomax = egi[l];
            }
            mennyi += belsomax;
            DP[i] = mennyi;
        }


    }
    cout << DP[targyszam-1];

    return 0;
}

