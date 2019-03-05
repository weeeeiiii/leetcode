#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;

struct mofan{
    int op[2][4];
    int step;
    vector<char> buzhou;
}s,temp;
int b[2][4];
queue<mofan> q;

mofan transform(mofan node,int i)
{
    mofan temp;
    if(i==0)
    {
        swap(node.op[0][0],node.op[1][0]);
        swap(node.op[0][1],node.op[1][1]);
        swap(node.op[0][2],node.op[1][2]);
        swap(node.op[0][3],node.op[1][3]);
        for(int m=0;m<2;m++)
        {
            for(int j=0;j<4;j++)
            {
                temp.op[m][j]=node.op[m][j];
            }
        }
        temp.buzhou=node.buzhou;
        temp.buzhou.push_back('A');
        temp.step=node.step+1;
    }
    else if(i==1)
    {
        swap(node.op[0][0],node.op[0][3]);
        swap(node.op[1][0],node.op[1][3]);
        swap(node.op[0][1],node.op[0][3]);
        swap(node.op[1][1],node.op[1][3]);
        swap(node.op[0][2],node.op[0][3]);
        swap(node.op[1][2],node.op[1][3]);
        for(int m=0;m<2;m++)
        {
            for(int j=0;j<4;j++)
            {
                temp.op[m][j]=node.op[m][j];
            }
        }
        temp.buzhou=node.buzhou;
        temp.buzhou.push_back('B');
        temp.step=node.step+1;
    }
    else if(i==2)
    {
        swap(node.op[0][1],node.op[0][2]);
        swap(node.op[0][1],node.op[1][2]);
        swap(node.op[0][1],node.op[1][1]);
        for(int m=0;m<2;m++)
        {
            for(int j=0;j<4;j++)
            {
                temp.op[m][j]=node.op[m][j];
            }
        }
        temp.buzhou=node.buzhou;
        temp.buzhou.push_back('C');
        temp.step=node.step+1;
    }
    return temp;
}

void BFS()
{
    for(int i=0;i<4;i++)
    {
        s.op[0][i]=i+1;
    }
    for(int i=0;i<4;i++)
    {
        s.op[1][i]=8-i;
    }
    s.step=0;
    q.push(s);
    int flag=1;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(s.op[i][j]!=b[i][j]) flag=0;
        }
    }

    if(flag==1)
    {
        printf("0\n\n");
        return;
    }

    while(!q.empty())
    {
        mofan node=q.front();
        q.pop();

        for(int i=0;i<3;i++)
        {
            if(i==0)
            {
                temp=transform(node,i);
            }
            else if(i==1)
            {
                temp=transform(node,i);
            }
            else if(i==2)
            {
                temp=transform(node,i);
            }
            q.push(temp);
            int flag=1;
            for(int m=0;m<2;m++)
            {
                for(int j=0;j<4;j++)
                {
                    if(temp.op[m][j]!=b[m][j]) flag=0;
                }
            }
            if(flag==1)
            {
                printf("%d\n",temp.step);
                int num=0;
                for(vector<char>::iterator it=temp.buzhou.begin();it!=temp.buzhou.end();it++)
                {
                    if(num>0&&num%60==0) printf("\n");
                    num++;
                    printf("%c",*it);
                }
                printf("\n");
                while(!q.empty()) q.pop();
                return;
            }

        }
    }
    return;
}

int main()
{
    int t[8];
    while(cin>>t[0])
    {
        getchar();
        for(int i=1;i<8;i++)
        {
            scanf("%d",t+i);
            getchar();
        }
        for(int i=0;i<4;i++)
        {
            b[0][i]=t[i];
        }
        for(int i=0;i<4;i++)
        {
            b[1][i]=t[8-i-1];
        }
        BFS();
    }
    return 0;
}
