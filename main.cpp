#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>

using namespace std;

int a[3][3],b[3][3];
int X[4] = {0, 0, 1, -1};
int Y[4] = {1, -1, 0, 0};
struct node{
    int x,y;
    int step;
    int matrix[3][3];
    int last[2];
}s,temp;

bool check(int x,int y)
{
    if(x<0||x>=3||y<0||y>=3)
        return false;
    return true;
}

bool same(int a[3][3])
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(a[i][j]!=b[i][j])
                return false;
        }
    return true;
}

int BFS(int x,int y)
{
    queue<node> q;
    s.x=x,s.y=y;
    s.step=1;
    s.last[0]=x,s.last[1]=y;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            s.matrix[i][j]=a[i][j];
        }
    }
    q.push(s);

    while(!q.empty())
    {
        node top=q.front();
        q.pop();

        for(int i=0;i<4;i++)
        {
            int new_x=top.x+X[i];
            int new_y=top.y+Y[i];
            if(check(new_x,new_y)&&(new_x!=top.last[0]||new_y!=top.last[1]))
            {
                temp.x=new_x;
                temp.y=new_y;
                temp.step=top.step+1;
                temp.last[0]=top.x;
                temp.last[1]=top.y;
                for(int i=0;i<3;i++)
                {
                    for(int j=0;j<3;j++)
                    {
                        temp.matrix[i][j]=top.matrix[i][j];
                    }
                }
                swap(temp.matrix[new_x][new_y],temp.matrix[top.x][top.y]);
                if(same(temp.matrix))
                {
                    return temp.step;
                }
                q.push(temp);
            }
        }
    }
}

int main()
{
    int x,y;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            scanf("%d",&a[i][j]);
            if(a[i][j]==0)
            {
                x=i;
                y=j;
            }
            getchar();
        }
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            scanf("%d",&b[i][j]);
            getchar();
        }
    }

    int step=BFS(x,y);
    printf("%d",step);
    return 0;
};























