#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
#define N 10010
using namespace std;

int T,n;
queue<string> all[N];
string now[N]; //存放当前的指令
bool finish[N]={false}; //判断这个进程是否结束
void clean()
{
    for(int i=0;i<N;i++) finish[i]=false;

}

int panduan()
{
    for(int i=0;i<n;i++)
    {
        if(!finish[i])
        {
            if(now[i][0]=='R')
            {
                int num=now[i][1]-'0';
                if(finish[num]) continue;
                if(now[num][0]=='S'&&(now[num][1]-'0')==i)
                {
                    if(all[i].size()>1)
                    {
                        all[i].pop();
                        now[i]=all[i].front();
                    }
                    else finish[i]=true;
                    if(all[num].size()>1)
                    {
                        all[num].pop();
                        now[num]=all[num].front();
                    }
                    else finish[num]=true;

                    return 1;
                }
            }
        }
        if(i==n-1) return 0;
    }
}

void init()
{
    for(int i=0;i<n;i++)
    {
        now[i]=all[i].front();
    }
}

int main()
{
    scanf("%d%d",&T,&n);
    while(T--)
    {
        clean();
        int number=0;
        for(int i=0;i<n;i++)
        {
            char ch=1;
            while(ch!='\n')
            {
                string t;
                char ui[10];
                scanf("%s",ui);
                t=ui;
                number++;
                all[i].push(t);
                ch=getchar();
            }
        }
        init();
        int tag=0;
        for(int i=0;i<number/2;i++)
        {
           if(!panduan())
           {
               tag=1;
               break;
           }
        }
        printf("%d\n",tag);
    }
    return 0;
}