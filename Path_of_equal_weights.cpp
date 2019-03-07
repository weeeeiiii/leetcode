#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Node{
    int weight;
    vector<int> child;
}node[105];

int num,non_leaf,s;  //结点总数，不是叶子结点总数，目标值
int out[100];
bool cmp(int a,int b)
{
    return node[a].weight>node[b].weight;
}

void DFS(Node no,int index,int sum)
{
    if(sum>s) return;
    if(sum==s)
    {
        printf("%d ",node[0].weight);
        for(int i=0;i<index;i++)
        {
            printf("%d ",node[out[i]].weight);
        }
        printf("\n");
        return;
    }

    for(vector<int> ::iterator it=no.child.begin();it!=no.child.end();it++)
    {
        out[index]=*it;
        DFS(node[*it],index+1,sum+node[*it].weight);
    }
}

int main()
{
    scanf("%d%d%d",&num,&non_leaf,&s);
    for(int i=0;i<num;i++)
    {
        scanf("%d",&node[i].weight);
    }

    for(int i=0;i<non_leaf;i++)
    {
        int bianhao,shumu;
        int a[100];
        scanf("%d%d",&bianhao,&shumu);
        for(int i=0;i<shumu;i++)
        {
            scanf("%d",a+i);
        }
        sort(a,a+shumu,cmp);
        for(int i=0;i<shumu;i++)
        {
            node[bianhao].child.push_back(a[i]);
        }
    }

    DFS(node[0],0,node[0].weight);
    return 0;

}
