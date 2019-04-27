#include <iostream>

using namespace std;

int unio (int a, int p[], int b, int q[], int r[])
{
    int i=0, j=0, k=0;
    while (i<a & j<b)
    {
        if (p[i]==q[j])
        {
            r[k]=p[i];
            i++;
            j++;
            k++;
        }
        else if (p[i]<q[j])
        {
            r[k]=p[i];
            i++;
            k++;
        }
        else
        {
            r[k]=q[j];
            j++;
            k++;
        }
    }
    if (i==a)
    {
        while (j<=b)
        {
            r[k]=q[j];
            j++;
            k++;
        }
    }
    else
    {
        while (i<=a)
        {
            r[k]=p[i];
            i++;
            k++;
        }
    }
    return k-1;

}


int metszet (int a, int p[], int b, int q[], int m[])
{
    int i=0, j=0, k=0;
    while (i<a && j<b)
    {
        if (p[i]==q[j])
        {
            m[k]=p[i];
            k++;
            i++;
            j++;
        }
        else if (p[i]<q[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    return k;

}

int kulonbseg (int a, int p[], int b, int q[], int ku[])
{
     int i=0, j=0, l=0;
     while (i<a)
     {
         if (b==j || p[i]<q[j])
         {
             ku[l]=p[i];
             i++;
             l++;
         }
         else if (p[i]==q[j])
         {
             i++;
             j++;
         }
         else
         {
             j++;
         }
     }
     return l;
}

int multiunio (int a, int p[], int b, int q[], int mu[])
{
    int i=0, j=0, k=0;

    while (i<a || j<b)
    {
        if (a>i && b>j && p[i]<q[j])
        {
            mu[k]=p[i];
            k++;
            i++;
        }
        else if (a>i && b>j)
        {
            mu[k]=q[j];
            k++;
            j++;
        }
        else if (a>i)
        {
            mu[k]=p[i];
            k++;
            i++;
        }
        else
        {
            mu[k]=q[j];
            k++;
            j++;
        }
    }
    return k;
}

int main()
{
    //cout << "Hello world!" << endl;

    int p[]{1,3,7,8,12}, q[]{2,3,4,12}, r[100], m[100], ku[100], mu[100];
    //int c = unio(5,p,3,q,r);
    /*cout<<c<<endl;

    for (int w=0; w<c; w++)
    {
        cout << r[w]<<" ";
    }
    cout <<endl;
    int d= metszet(5,p,4,q,m);
    cout<<d<<endl;

    for (int w=0; w<d; w++)
    {
        cout << m[w]<<" ";
    }*/

    /*int e = kulonbseg(5,p,4,q,ku);
    cout <<e<<endl;

    for (int w=0; w<e; w++)
    {
        cout << ku[w]<<" ";
    }*/

    int f = multiunio(5,p,4,q, mu);
    cout <<f<<endl;

    for (int w=0; w<f; w++)
    {
        cout << ku[w]<<" ";
    }


    return 0;
}
