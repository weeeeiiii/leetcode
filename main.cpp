#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const int maxn=1010;
vector<int> adj[maxn];
int N,L;
bool visited[maxn];
int people=0;

void BFS(int u)
{
    int depth=0;
    queue<int> q;
    q.push(u);
    visited[u]=true;
    int length=(int)q.size();
    while(!q.empty()&&depth<L)
    {
        int wei=q.front();
        q.pop();
        length--;
        for(int i=0;i<adj[wei].size();i++)
        {
            if(visited[adj[wei][i]]) continue;
            visited[adj[wei][i]]=true;
            people++;
            q.push(adj[wei][i]);
        }
        if(length==0)
        {
            depth++;
            length=(int)q.size();
        }
    }
}

int main()
{
    scanf("%d%d",&N,&L);
    for(int i=0;i<N;i++)
    {
        int num;
        scanf("%d",&num);
        for(int m=0;m<num;m++)
        {
            int number;
            scanf("%d",&number);
            adj[number-1].push_back(i);
        }
    }

    int num_people;
    cin>>num_people;
    while(num_people--)
    {
        int sym;
        cin>>sym;
        people=0;
        for(int i=0;i<N;i++)
        {
            visited[i]=false;
        }
        BFS(sym-1);
        printf("%d",people);
        if(num_people>0) printf("\n");
    }
    return 0;
}