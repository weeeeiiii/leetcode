#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

int panduan(int number)
{
    if(number<=1) return 0;
    for(int i=2;i<number;i++)
    {
        if(number%i==0) return 0;
    }
    return 1;
}
int reverse(int num,int d)
{
    int a[100],cnt=0;
    do{
        a[cnt++]=num%d;
        num/=d;
    }while(num);
    int ans=0;
    for(int i=0;i<cnt;i++)ans=ans*d+a[i];
    return ans;
}
int N,D;
int main()
{
    cin>>N>>D;
    while(N>=0)
    {
        int re=reverse(N,D);
        if(panduan(N)&&panduan(re))
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
        scanf("%d",&N);
        if(N>0) scanf("%d",&D);
    }
    return 0;
}
