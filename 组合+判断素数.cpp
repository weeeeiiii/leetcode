#include<cstdio>
#include<algorithm>
using namespace std;

int n,k;
int n_num[30];
int flag[30]={0};
int sym=0;
int out[1000];


int sushu(int a)
{
    if(a==2||a==3)
        return 1;
    if(!(a&1))
        return 0;
    for(int i=3;i*i<=a;i+=2)
    {
        if(a%i==0)
            return 0;
    }
    return 1;
}

void DFS(int index,int x)
{
    if(index==k)
    {
        int sum=0;
        for(int i=0;i<k;i++)
        {
            sum+=n_num[out[i]];
        }
        if(sushu(sum)) sym++;
        return;
    }

    for(int i=x;i<n;i++)
    {
        if(flag[i]) continue;
        out[index]=i;
        flag[i]=1;
        DFS(index+1,i+1);
        flag[i]=0;
    }
}

int main()
{
    scanf("%d %d",&n,&k);
    for(int i=0;i<n;i++)
    {
        scanf("%d",n_num+i);
    }
    DFS(0,0);
    printf("%d",sym);
    return 0;
}




