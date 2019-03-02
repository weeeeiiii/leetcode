#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

int num[1000];

int main()
{
    int x;
    int n;
    scanf("%d",&x);
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        scanf("%d",&num[i]);
    }

    int flag=0;
    for(int i=0;i<n;i++)
    {
        if(num[i]==x)
        {
            swap(num[i],num[i+1]);
            flag=1;
            break;
        }
    }

    if(flag==0)
    {
        num[n]=x;
        n=n+1;
        sort(num,num+n);
        printf("no\n");
        for(int i=0;i<n;i++)
        {
            printf("%d ",num[i]);
        }
    }
    else
    {
        printf("%d\n",x);
        for(int i=0;i<n;i++)
        {
            printf("%d ",num[i]);
        }
    }
    return 0;
}
