#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

const int N=1010;
int n;
float a[N],b[N];
float c[2010];
int main()
{
    int number=0;
    int m;
    cin>>m;
    for(int j=0;j<m;j++)
    {
        int n_1;
        float n_2;
        cin>>n_1>>n_2;
        a[n_1]=n_2;
    }
    cin>>m;
    for(int j=0;j<m;j++)
    {
        int n_1;
        float n_2;
        cin>>n_1>>n_2;
        b[n_1]=n_2;
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(a[i]!=0&&b[j]!=0)
            {
                c[i+j]+=a[i]*b[j];
            }
        }
    }
    for(int i=0;i<2010;i++)
    {
        if(c[i]!=0) number++;
    }
    printf("%d",number);
    for(int i=2009;i>=0;i--)
    {
        if(c[i]!=0)
        {
            printf(" %d %.1f",i,c[i]);
        }
    }
    return 0;
}
