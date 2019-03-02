#include<cstdio>
#include<stack>

using namespace std;

int n;
int sum=0;
int out[100];

void DFS(int index,int length)
{
    if(index==n*2)
    {
        sum++;
        return;
    }

    if(length==0)
    {
        out[index]=1;
        DFS(index+1,length+1);
    }
    else
    {
        out[index]=0;
        DFS(index+1,length-1);
        out[index]=1;
        DFS(index+1,length+1);
    }
}

int main()
{
    scanf("%d",&n);
    DFS(0,0);
    sum=sum/(n+1);
    printf("%d",sum);
    return 0;
}