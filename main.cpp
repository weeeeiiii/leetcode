#include<cstdio>
#include<iostream>
#include<set>
#include<vector>
#include<stack>
using namespace std;
const int maxn=1010;
int n,m;
vector<int> adj[maxn];
bool visited[maxn]={false};
set<int> ori;
set<int> last;

void DFS()
{
    stack<int> s;
    s.push(1);
    visited[1]=true;
    last.insert(1);

    while(!s.empty())
    {
        int num=s.top();
        s.pop();
        for(int i=0;i<adj[num].size();i++)
        {
            if(visited[adj[num][i]]) continue;
            s.push(adj[num][i]);
            visited[adj[num][i]]=true;
            last.insert(adj[num][i]);
        }
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    while(n!=0)
    {
        for(int i=0;i<maxn;i++)
        {
            adj[i].clear();
        }
        ori.clear();
        last.clear();
        for(int i=1;i<=n;i++)
        {
            ori.insert(i);
        }
        for(int i=0;i<m;i++)
        {
            int num_1,num_2;
            cin>>num_1>>num_2;
            adj[num_1].push_back(num_2);
            adj[num_2].push_back(num_1);
        }
        for(int i=0;i<maxn;i++)
        {
            visited[i]=false;
        }
        DFS();
        if(ori==last)
        {
            printf("YES\n");
        }
        else printf("NO\n");
        scanf("%d%d",&n,&m);
    }
    return 0;
}