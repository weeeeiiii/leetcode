#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;

string N1,N2;
int tag;
string r;
int radix;
long long a;
long long zhuanhuan(string number,int jinzhi)
{
    int len=number.size();
    long long sum=0;
    int n=0;
    while(len--)
    {
        if('0'<=number[len]&&number[len]<='9')
        {
            int num=number[len]-'0';
            if(num>=jinzhi) return 0;
            long long jiashu=1;
            for(int i=0;i<n;i++)
            {
                jiashu*=jinzhi;
            }
            sum+=num*jiashu;
            n++;
        }
        else if('a'<=number[len]&&number[len]<='z')
        {
            int num=number[len]-'a'+10;
            if(num>=jinzhi) return 0;
            long long jiashu=1;
            for(int i=0;i<n;i++)
            {
                jiashu*=jinzhi;
            }
            sum+=num*jiashu;
            n++;
        }
    }
    return sum;
}
int main()
{
    cin>>N1>>N2>>tag>>radix;
    if(tag==1)
    {
        a=zhuanhuan(N1,radix);
        for(int i=2;i<=100000;i++)
        {
            long long b=zhuanhuan(N2,i);
            if(a==b)
            {
                printf("%d",i);
                return 0;
            }
            else if(b>a)
            {
                printf("Impossible");
                return 0;
            }
        }
    }
    else if(tag==2)
    {
        a=zhuanhuan(N2,radix);
        for(int i=2;i<=100000;i++)
        {
            long long b=zhuanhuan(N1,i);
            if(a==b)
            {
                printf("%d",i);
                return 0;
            }
            else if(b>a)
            {
                printf("Impossible");
                return 0;
            }
        }
    }
}
