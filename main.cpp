#include<cstdio>

using namespace std;

int out[10];
int n;
int flag[10]={0};
int tag=0;

int hege(int out[],int num)
{
    for(int i=0;i<num;i++)
    {
        int add=1;
        while(add+i<num||(i-add>=0))
        {
            if((add+i<num)&&(out[i]+add)==(out[add+i]))
            {
                return 0;
            }
            if((add+i<num)&&(out[i]-add)==(out[add+i])) return 0;
            if((i-add>=0)&&(out[i-add])==(out[i]+add)) return 0;
            if((i-add>=0)&&(out[i-add])==(out[i]-add)) return 0;
            add++;
        }
    }
    return 1;
}

void DFS(int index)
{
    if(index==n)
    {
        if(hege(out,n))
        {
            tag=1;
            for(int i=0;i<n;i++)
            {
                printf("%d ",out[i]);
            }
            printf("\n");
        }
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
    if(tag==0)
    {
        printf("no solute!");
    }
    return 0;
}






