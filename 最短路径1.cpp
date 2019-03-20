#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn=110;
const int INF=-1;
int father[maxn],d[maxn][maxn];
int n;
int QuickPow(int a,int b,int m)
{
    long long x=a;
    int ans=1;
    while(b>0)
    {
        if(b&1)
        {
            ans=ans*x%m;
        }
        x=x*x%m;
        b=b>>1;
    }
    return ans;
}
void init(int n)
{
    for(int i=0;i<n;++i)
    {
        father[i]=i;
        d[i][i]=0;
    }
}
int findFather(int a)
{
    while(a!=father[a])
        a=father[a];
    return a;
}
int main()
{
    int m,u,v;
    while(~scanf("%d %d",&n,&m))
    {
        fill(d[0],d[0]+maxn*maxn,INF);
        init(n);
        for(int k=0;k<m;++k)
        {
            scanf("%d %d",&u,&v);
            int x=findFather(u);
            int y=findFather(v);
            if(x!=y)
            {
                int num=QuickPow(2,k,100000);
                for(int i=0;i<n;++i)
                {
                    if(x==findFather(i))
                    {
                        for(int j=0;j<n;++j)
                        {
                            if(y==findFather(j))
                            {
                                d[i][j]=d[j][i]=(num+d[i][u]+d[j][v])%100000;
                            }
                        }
                    }
                }
            }
            father[y]=x;
        }
        for(int i=1;i<n;++i)
            printf("%d\n",d[0][i]);
    }
    return 0;
}
