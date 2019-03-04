#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

char a[8][9];
int dx[] = {0, 1, -1, 0, 0, -1, 1, -1, 1};
int dy[] = {0, 0, 0, 1, -1, 1, 1, -1, -1};
bool flag;

struct node{
    int x, y;
    int step;
}s, temp;

bool check(int x, int y)
{
    if(x >= 8 || x < 0 || y >= 8 || y < 0)
        return false;
    return true;
}

void bfs()
{
    int i, j;
    s.x = 7;
    s.y = 0;
    s.step = 0;
    queue<node>q;
    q.push(s);
    while(!q.empty())
    {

        s = q.front();
        q.pop();

        for(i = 0;i < 9; i++)
        {
            temp.x = s.x + dx[i];
            temp.y = s.y + dy[i];
            temp.step = s.step + 1;
            /*因为我们记下来所走的步数为step，所以判断点a[temp.x-temp.step+1][temp.y]是否为石头即可知道所走的下一步是否为石头
            点a[temp.x-temp.step][temp.y]即为所走点的上面是否为石头*/
            if(check(temp.x, temp.y) && a[temp.x-temp.step][temp.y] != 'S' && a[temp.x-temp.step+1][temp.y] != 'S')
            {
                //用判断是否走满了八步来代替判重
                if(a[temp.x][temp.y] == 'A' || temp.step > 8)
                {
                    flag = 1;
                    return ;
                }
                q.push(temp);
            }
        }
    }
    return ;
}

int main()
{
    int t, i, j, k;
    scanf("%d", &t);
    k = 1;
    getchar();
    while(t--)
    {

        for(i = 0; i < 8; i++)
        {
            scanf("%s", a[i]);


        }
        flag = 0;
        bfs();
        printf("Case #%d: ", k);
        if(flag)
            printf("Yes\n");
        else
            printf("No\n");
        k++;
    }
    return 0;
}