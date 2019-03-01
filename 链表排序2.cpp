#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Node{
    int number;
    int grade;
}node[10000];

bool cmp(Node a,Node b)
{
    return a.number<b.number;
}

int main()
{
    int N,M;
    scanf("%d %d",&N,&M);
    for(int i=0;i<N+M;i++)
    {
        scanf("%d %d",&node[i].number,&node[i].grade);
    }
    sort(node,node+M+N,cmp);
    for(int i=0;i<M+N;i++)
    {
        printf("%d %d\n",node[i].number,node[i].grade);
    }
    return 0;
}
