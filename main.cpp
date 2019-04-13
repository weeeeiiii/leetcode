#include<cstdio>
#include<iostream>
using namespace std;

const int N=1010;
int G[N][N];
int father[N];
int n,m,k;
void init()
{
    for(int i=0;i<N;i++)
    {
        father[i]=i;
    }
}
int findfather(int x)
{
    int a=x;
    while(x!=father[x])
    {
        x=father[x];
    }
    while(a!=father[a])
    {
        int z=a;
        a=father[a];
        father[z]=x;
    }
    return x;
}
void Uion(int a,int b)
{
    int fa=findfather(a);
    int fb=findfather(b);
    if(fa!=fb)
    {
        father[fa]=fb;
    }
}

int main()
{
    fill(G[0],G[0]+N*N,0);
    cin>>n>>m>>k;
    for(int i=0;i<m;i++)
    {
        int num_1,num_2;
        cin>>num_1>>num_2;
        G[num_1-1][num_2-1]=1;
        G[num_2-1][num_1-1]=1;
    }
    for(int i=0;i<k;i++)
    {
        init();
        int num;
        cin>>num;
        num=num-1;
        for(int j=0;j<n;j++)
        {
            for(int m=0;m<n;m++)
            {
                if(G[j][m]==1&&j!=num&&m!=num)
                {
                    Uion(j,m);
                }
            }
        }
        int lianton=0;
        for(int j=0;j<n;j++)
        {
            if(father[j]==j) lianton++;
        }
        printf("%d\n",lianton-2);
    }
    return 0;
}