#include<cstdio>
#include<iostream>

using namespace std;

int a[20][20],endx,endy,m,n;
int startx,starty;
int flag=0;
int dx[4] = { 0,-1,0,1 }, dy[4] = { -1,0,1,0 };

struct Route{
    int x,y;
}route[5000];

void DFS(int x,int y,int index)
{
    if(x==endx&&y==endy)
    {
        flag=1;
        for(int i=0;i<index;i++)
        {
            printf("(%d,%d)->",route[i].x,route[i].y);
        }
        printf("(%d,%d)\n",endx,endy);
        return;
    }

    route[index].x=x;
    route[index].y=y;
    for(int i=0;i<4;i++)
    {
        if(a[x+dx[i]][y+dy[i]]==1&&1<=x+dx[i]<=m&&1<=y+dy[i]<=n)
        {
            a[x][y]=0;   //让这条曲线不能往回走,以免陷入循环
            DFS(x+dx[i],y+dy[i],index+1);
            a[x][y]=1;
        }
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    scanf("%d%d",&startx,&starty);
    scanf("%d%d",&endx,&endy);
    DFS(startx,starty,0);
    if(flag==0)
    {
        printf("-1");
    }
    return 0;
}