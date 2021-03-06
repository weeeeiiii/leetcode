#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;
const int maxn=60,INF=10000;
int G[maxn][maxn];
int d[maxn];
int n,s;
bool visited[maxn]={false};

void dijie(int qishi)
{
    for(int i=0;i<maxn;i++)
    {
        d[i]=INF;
    }
    d[qishi]=0;

    for(int i=0;i<n;i++)
    {
        int u=-1,min=INF;
        for(int j=0;j<n;j++)
        {
            if(!visited[j]&&min>d[j])
            {
                u=j;
                min=d[j];
            }
        }
        if(u==-1) return;

        visited[u]=true;
        for(int v=0;v<n;v++)
        {
            if(!visited[v]&&G[u][v]!=INF&&(d[u]+G[u][v]<d[v]))
            {
                d[v]=d[u]+G[u][v];
            }
        }
    }
}

int main()
{
    scanf("%d%d",&n,&s);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            G[i][j]=INF;
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int num;
            cin>>num;
            if(num==0)
            {
                G[i][j]=INF;
                continue;
            }
            G[i][j]=num;
        }
    }

    dijie(s);

    for(int i=0;i<n;i++)
    {
        if(i==s) continue;
        if(d[i]==INF)
        {
            printf("-1 ");
        }
        else printf("%d ",d[i]);
    }
    printf("\n");
    return 0;
}
