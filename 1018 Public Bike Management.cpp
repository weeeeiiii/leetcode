#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

const int INF=100000;
bool visited[510]={false};
int C,N,S,M;
int G[510][510];
int bike[510];
int out[510];
struct Node{
    int length;
    vector<int> a;
    int need=0;
    int back=0;
    int number=0;
};
int cmp(Node a,Node b)
{
    if(a.number!=b.number) return a.number<b.number;
    if(a.need!=b.need) return a.need<b.need;
    return a.back<b.back;
}
vector<Node> v;

void DFS(int index)
{
    int num=out[index-1];
    if(num==S)
    {
        Node temp;
        temp.length=index;
        temp.a.push_back(0);
        for(int i=1;i<index;i++)
        {
            temp.a.push_back(out[i]);
        }
        for(int i=0;i<temp.length-1;i++)
        {
            int num_1,num_2;
            num_1=temp.a[i];
            num_2=temp.a[i+1];
            temp.number+=G[num_1][num_2];
        }
        v.push_back(temp);
        return;
    }
    for(int i=0;i<=N;i++)
    {
        if(visited[i]||G[num][i]==INF) continue;
        out[index]=i;
        visited[i]=true;
        DFS(index+1);
        visited[i]=false;
    }
}

int main()
{
    cin>>C>>N>>S>>M;
    fill(G[0],G[0]+500*500,INF);
    for(int i=0;i<N;i++)
    {
        cin>>bike[i+1];
    }
    for(int i=0;i<M;i++)
    {
        int num_1,num_2,num_3;
        cin>>num_1>>num_2>>num_3;
        G[num_1][num_2]=num_3;
        G[num_2][num_1]=num_3;
    }
    out[0]=0;
    visited[0]=true;
    DFS(1);

    for(int i=0;i<v.size();i++)
    {
        int need=0,back=0;
        for(int j=1;j<v[i].length;j++)
        {
            int num=v[i].a[j];
            if(bike[num]>=C/2)     //不需要车
            {
                back+=bike[num]-C/2;
            }
            else
            {
                int xuyao=C/2-bike[num];
                if(back>xuyao)
                {
                    need+=0;
                    back=back-xuyao;
                }
                else
                {
                    need+=xuyao-back;
                    back=0;
                }
            }
        }
        v[i].need=need;
        v[i].back=back;
    }
    sort(v.begin(),v.begin()+v.size(),cmp);
    printf("%d ",v[0].need);
    for(int i=0;i<v[0].length;i++)
    {
        printf("%d",v[0].a[i]);
        if(i<v[0].length-1) printf("->");
    }
    printf(" %d",v[0].back);
    return 0;
}
