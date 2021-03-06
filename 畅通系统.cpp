#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int father[1000]={0};

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

void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        father[i]=i;
    }
}

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    while(1)
    {
        if(n==0) break;
        init(n);
        for(int i=0;i<m;i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            Union(a,b);
        }
        int count=-1;
        for(int i=1;i<=n;i++)
        {
            if(father[i]==i) count++;
        }

        printf("%d\n",count);
        scanf("%d",&n);
        if(n==0) break;
        scanf("%d",&m);
    }
    return 0;
}
