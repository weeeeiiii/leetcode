#include<cstdio>
#include<iostream>
using namespace std;

const int maxn=100,INF=1000000;
int n,m;
int G[maxn][maxn];
int d[maxn];
bool visited[maxn]={false};
int ans=0;

int prim(int s)
{
    fill(d,d+maxn,INF);
    for(int i=0;i<maxn;i++)
    {
        visited[i]=false;
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
        if(u==-1) return -1;
        visited[u]=true;
        ans+=d[u];
        for(int v=0;v<n;v++)
        {
            if(!visited[v]&&G[u][v]!=INF&&G[u][v]<d[v])
            {
                d[v]=G[u][v];
            }
        }
    }
    return ans;
}

int main()
{
    scanf("%d%d",&m,&n);
    while(m!=0)
    {
        ans=0;
        fill(G[0],G[0]+maxn*maxn,INF);
        for(int i=0;i<m;i++)
        {
            int num_1,num_2,len;
            cin>>num_1>>num_2>>len;
            G[num_1-1][num_2-1]=G[num_2-1][num_1-1]=len;
        }
        int num=prim(0);
        if(num==-1) printf("?\n");
        else printf("%d\n",num);
        cin>>m>>n;
    }
    return 0;
}