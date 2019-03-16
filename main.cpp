#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const int maxn=520,INF=10000;
int N,M,C1,C2;
int G[maxn][maxn];
int cost[maxn][maxn];
int d_cost[maxn];
int d[maxn];
bool visited[maxn]={false};
int pre[maxn];

void Dijie(int s)
{
    for(int i=0;i<maxn;i++)
    {
        d[i]=INF;
        d_cost[i]=0;
    }
    d[s]=0;
    for(int i=0;i<N;i++)
    {
        int u=-1,min=INF;
        for(int j=0;j<N;j++)
        {
            if(!visited[j]&&d[j]<min)  //找到没访问的点中最短的点
            {
                u=j;
                min=d[j];
            }
        }
        if(u==-1) return;
        visited[u]=true;
        for(int j=0;j<N;j++)
        {
            if(!visited[j]&&G[u][j]!=INF)
            {
                if(d[u]+G[u][j]<d[j])
                {
                    d[j]=d[u]+G[u][j];
                    d_cost[j]=d_cost[u]+cost[u][j];
                    pre[j]=u;
                }
                else if(d[u]+G[u][j]==d[j]&&d_cost[j]>d_cost[u]+cost[u][j])
                {
                    d_cost[j]=d_cost[u]+cost[u][j];
                    pre[j]=u;
                }
            }
        }
    }
}

void DFS(int s,int v)
{
    if(v==s)
    {
        printf("%d ",s);
        return;
    }
    DFS(s,pre[v]);
    printf("%d ",v);
}
int main()
{
    scanf("%d%d%d%d",&N,&M,&C1,&C2);
    fill(G[0],G[0]+maxn*maxn,INF);
    fill(cost[0],cost[0]+maxn*maxn,INF);
    for(int i=0;i<M;i++)
    {
        int c1,c2,l,m;
        scanf("%d%d",&c1,&c2);
        scanf("%d%d",&l,&m);
        G[c1][c2]=l;
        G[c2][c1]=l;
        cost[c1][c2]=m;
        cost[c2][c1]=m;
    }
    Dijie(C1);
    DFS(C1,C2);
    printf("%d %d",d[C2],d_cost[C2]);
    return 0;
}