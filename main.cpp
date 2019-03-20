#include<cstdio>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

const int maxn=1010,INF=100000;
int G[maxn][maxn];
int G_cost[maxn][maxn];
int d[maxn];
int cost[maxn];
bool visited[maxn]={false};
int n,m;

void dijie(int s)
{
    for(int i=0;i<maxn;i++)
    {
        visited[i]=false;
    }
    fill(d,d+maxn,INF);
    fill(cost,cost+maxn,INF);
    d[s]=0;
    cost[s]=0;
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
            if(!visited[v]&&G[u][v]!=INF)
            {
                if(d[u]+G[u][v]<d[v])
                {
                    d[v]=d[u]+G[u][v];
                    cost[v]=cost[u]+G_cost[u][v];
                }
                else if(d[u]+G[u][v]==d[v]&&cost[u]+G_cost[u][v]<cost[v])
                {
                    cost[v]=cost[u]+G_cost[u][v];
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    while(n!=0)
    {
        fill(G[0],G[0]+maxn*maxn,INF);
        fill(G_cost[0],G_cost[0]+maxn*maxn,INF);
        for(int i=0;i<m;i++)
        {
            int num_1,num_2,len,p;
            cin>>num_1>>num_2>>len>>p;
            G[num_1-1][num_2-1]=G[num_2-1][num_1-1]=len;
            G_cost[num_1-1][num_2-1]=G_cost[num_2-1][num_1-1]=p;
        }
        int start,end;
        cin>>start>>end;
        dijie(start-1);
        printf("%d %d\n",d[end-1],cost[end-1]);
        cin>>n>>m;
    }
    return 0;
}