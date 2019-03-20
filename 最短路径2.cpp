#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

const int maxn=10010,INF=10000;
int G[maxn][maxn];
int pre[maxn];
bool visited[maxn]={false};
int d[maxn];
int n,m,start,end_1;

void dijie(int s)
{
    for(int i=0;i<maxn;i++)
    {
        d[i]=INF;
    }
    d[s]=0;

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
            if(!visited[v]&&G[u][v]!=INF&&(G[u][v]+d[u]<d[v]))
            {
                d[v]=G[u][v]+d[u];
                pre[v]=u;
            }
        }
    }
}
void DFS(int s,int v)
{
    if(v==s)
    {
        printf("%d ",s+1);
        return;
    }
    DFS(s,pre[v]);
    printf("%d ",v+1);
}

int main()
{
    for(int i=0;i<maxn;i++)
    {
        for(int j=0;j<maxn;j++)
        {
            G[i][j]=INF;
        }
    }
    scanf("%d%d%d%d",&n,&m,&start,&end_1);
    for(int i=0;i<m;i++)
    {
        int num_1,num_2,len;
        cin>>num_1>>num_2>>len;
        if(G[num_1][num_2]>len)
        {
            G[num_1 - 1][num_2 - 1] = G[num_2 - 1][num_1 - 1] = len;
        }
    }
    dijie(start-1);
    if(d[end_1-1]==INF)
    {
        printf("can't arrive");
    }
    else
    {
        printf("%d\n",d[end_1-1]);
        DFS(start-1,end_1-1);
    }
    return 0;
}
