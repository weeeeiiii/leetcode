#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int sum=0;
float a[2010];

int main()
{
    for(int i=0;i<2010;i++)
    {
        a[i]=0;
    }
    int num;
    scanf("%d",&num);
    while(num--)
    {
        int q;
        float w;
        scanf("%d%f",&q,&w);
        a[q]+=w;
    }
    scanf("%d",&num);
    while(num--)
    {
        int q;
        float w;
        scanf("%d%f",&q,&w);
        a[q]+=w;

    }
    for(int i=0;i<2010;i++)
    {
        if(a[i]!=0) sum++;
    }
    printf("%d",sum);
    for(int i=1500;i>=0;i--)
    {
        if(a[i]==0) continue;
        else
        {
            printf(" %d %.1f",i,a[i]);
        }
    }
    return 0;
}