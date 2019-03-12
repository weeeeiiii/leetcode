#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

const int maxn=10000010;
int father[maxn];
int flag[maxn];

int findFather(int a)
{
    int x=a;
    while(x!=father[x])
    {
        x=father[x];
    }
    while(a!=father[a])
    {
        int z=a;
        a=father[a];
        father[z]=x;
    }
    return x;
}

void Union(int a,int b)
{
    int fa=findFather(a);
    int fb=findFather(b);
    if(fa!=fb)
    {
        father[fa]=fb;
    }
}

void init()
{
    for(int i=1;i<maxn;i++)
    {
        father[i]=i;
        flag[i]=0;
    }
}

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0)
        {
            printf("1\n");
            continue;
        }
        init();
        for(int i=0;i<n;i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            Union(a,b);
        }

        for(int i=1;i<maxn;i++)
        {
            flag[findFather(i)]++;
        }

        int max=flag[1];
        for(int i=2;i<maxn;i++)
        {
            if(max<flag[i]) max=flag[i];
        }
        printf("%d\n",max);
        getchar();
    }
    return 0;
}
