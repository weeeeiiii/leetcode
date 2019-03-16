#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn=520,INF=10000;
int N,M,C1,C2;
int G[maxn][maxn];
int d[maxn];
int people[maxn];
int p[maxn];
int num[maxn];
bool visited[maxn]={false};


void Dijie(int s)
{
    for(int i=0;i<maxn;i++)
    {
        d[i]=INF;
    }
    for(int i=0;i<maxn;i++)
    {
        num[i]=0;
    }
    for(int i=0;i<maxn;i++)
    {
        p[i]=0;
    }
    d[s]=0;
    p[s]=people[s];
    num[s]=1;
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
                    p[j]=p[u]+people[j];
                    num[j]=num[u];
                }
                else if(d[u]+G[u][j]==d[j])
                {
                    if(p[u]+people[j]>p[j])
                    {
                        p[j] = p[u] + people[j];
                    }
                    num[j]+=num[u];
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d%d%d",&N,&M,&C1,&C2);
    for(int i=0;i<N;i++)
    {
        scanf("%d",&people[i]);

    }
    fill(G[0],G[0]+maxn*maxn,INF);
    for(int i=0;i<M;i++)
    {
        int c1,c2,l;
        scanf("%d%d",&c1,&c2);
        scanf("%d",&l);
        G[c1][c2]=l;
        G[c2][c1]=l;
    }
    Dijie(C1);
    printf("%d %d",num[C2],p[C2]);
    return 0;
}
