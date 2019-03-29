#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int maxn=110;
int n,m;
struct Node{
    int number;
    int level=0;
};
vector<Node>G[maxn];
bool child[maxn]={false};   //记录该节点是否是叶子节点
int jieguo[maxn];
int ma=1;
bool visited[maxn]={false};

void BFS()
{
    Node start;
    start.number=1;
    start.level=1;
    queue<Node> q;
    q.push(start);
    while(!q.empty())
    {
        Node temp=q.front();
        q.pop();
        int num=temp.number;
        for(int i=0;i<G[num].size();i++)
        {
            Node temp2=G[num][i];
            temp2.level=temp.level+1;
            G[num][i].level=temp2.level;
            if(temp2.level>ma) ma=temp2.level;
            q.push(temp2);
        }
    }
}

int main()
{
    cin>>n>>m;
    if(n==0)
    {
        printf("0");
        return 0;
    }
    if(n==1)
    {
        printf("1");
        return 0;
    }
    if(m==0)
    {
        printf("%d",n);
        return 0;
    }
    for(int i=0;i<maxn;i++)
    {
        jieguo[i]=0;
    }
    for(int i=0;i<m;i++)
    {
        int num_1,num;
        cin>>num_1>>num;
        child[num_1]=true;
        for(int j=0;j<num;j++)
        {
            int num_2;
            cin>>num_2;
            Node temp;
            temp.number=num_2;
            temp.level=0;
            G[num_1].push_back(temp);
        }
    }

    BFS();

    for(int i=1;i<=n;i++)
    {
        for(int m=0;m<G[i].size();m++)
        {
            Node temp=G[i][m];
            if(!child[temp.number])
            {
                jieguo[temp.level]++;
            }
        }
    }

    for(int i=1;i<=ma;i++)
    {
        printf("%d",jieguo[i]);
        if(i<ma) printf(" ");
    }
    return 0;
}