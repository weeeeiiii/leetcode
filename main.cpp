#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
const int maxn=100;
int n,inDegree[maxn];
vector<int> G[maxn];
int num=0;
vector<int> out;

void toposort()
{
    stack<int> q;
    for(int i=0;i<n;i++)
    {
        if(inDegree[i]==0)
        {
            q.push(i);
        }
    }

    while(!q.empty())
    {
        int u=q.top();
        q.pop();
        out.push_back(u);
        for(int i=0;i<G[u].size();i++)
        {
            int v=G[u][i];
            inDegree[v]--;
            if(inDegree[v]==0)
            {
                q.push(v);
            }
        }
        G[u].clear();
        num++;
    }
    if(num==n)
    {
        for(int i=0;i<n;i++)
        {
            printf("%d ",out[i]);
        }
        printf("\n");
    }
    else
    {
        printf("ERROR\n");
    }
}
int main()
{
    scanf("%d",&n);
    fill(inDegree,inDegree+maxn,0);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int sym;
            scanf("%d",&sym);
            if(sym==1)
            {
                G[i].push_back(j);
                inDegree[j]++;
            }
        }
    }
    toposort();
    return 0;
}