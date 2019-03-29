#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
const int maxn=510;
int n,m,inDegree[maxn];
vector<int> G[maxn];
vector<int> out;

void toposort()
{
    priority_queue<int,vector<int>,greater<int>> q;
    int num=0;
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
    for(int i=0;i<n;i++)
    {
        printf("%d",out[i]+1);
        if(i<out.size()-1) printf(" ");
    }
    out.clear();
}
int main()
{
    scanf("%d%d",&n,&m);
    while(n!=0)
    {
        fill(inDegree,inDegree+maxn,0);
        for(int i=0;i<maxn;i++)
        {
            G[i].clear();
        }
        for(int i=0;i<m;i++)
        {
            int num_1,num_2;
            cin>>num_1>>num_2;
            G[num_1-1].push_back(num_2-1);
            inDegree[num_2-1]++;
        }
        toposort();
        scanf("%d%d",&n,&m);
        if(n!=0) printf("\n");
    }
    return 0;
}
