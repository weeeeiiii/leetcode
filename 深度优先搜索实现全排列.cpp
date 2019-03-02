#include<cstdio>
int n,out[1000];
int flag[1000]={0};
using namespace std;

void DFS(int index)
{
    if(index==n)
    {
        for(int i=0;i<n;i++)
        {
            printf("%d",out[i]);
            if(i<n-1) printf(" ");
        }
        printf("\n");
        return;
    }

    for(int i=1;i<=n;i++)
    {
        if(flag[i]) continue;
        out[index]=i;
        flag[i]=1;
        DFS(index+1);
        flag[i]=0;
    }
}

int main()
{
    scanf("%d",&n);
    DFS(0);
    return 0;
}
