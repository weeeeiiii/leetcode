#include<iostream>
#include<queue>
using namespace std;

struct Node{
    int a,b,c;
    int step;
}s,temp;
int ca,cb,cc;
int n;
int sym=0;
int flag[105][105][105];

Node transform(Node node,int i)
{
    Node temp;
    temp.step=node.step+1;
    if(i==0)
    {
        if(node.a+node.b>cb)
        {
            temp.a=node.a+node.b-cb;
            temp.b=cb;
            temp.c=node.c;
        }
        else
        {
            temp.a=0;
            temp.b=node.a+node.b;
            temp.c=node.c;
        }
    }
    else if(i==1)
    {
        if(node.a+node.c>cc)
        {
            temp.a=node.a+node.c-cc;
            temp.b=node.b;
            temp.c=cc;
        }
        else
        {
            temp.a=0;
            temp.b=node.b;
            temp.c=node.a+node.c;
        }
    }
    else if(i==2)
    {
        if(node.b+node.a>ca)
        {
            temp.a=ca;
            temp.b=node.b+node.a-ca;
            temp.c=node.c;
        }
        else
        {
            temp.a=node.a+node.b;
            temp.b=0;
            temp.c=node.c;
        }
    }
    else if(i==3)
    {
        if(node.b+node.c>cc)
        {
            temp.a=node.a;
            temp.b=node.b+node.c-cc;
            temp.c=cc;
        }
        else
        {
            temp.a=node.a;
            temp.b=0;
            temp.c=node.b+node.c;
        }
    }
    else if(i==4)
    {
        if(node.c+node.a>ca)
        {
            temp.a = ca;
            temp.b = node.b;
            temp.c = node.a + node.c - ca;
        }
        else
        {
            temp.a=node.a+node.c;
            temp.b=node.b;
            temp.c=0;
        }
    }
    else if(i==5)
    {
        if(node.c+node.b>cb)
        {
            temp.a=node.a;
            temp.b=cb;
            temp.c=node.c+node.b-cb;
        }
        else
        {
            temp.a=node.a;
            temp.b=node.c+node.b;
            temp.c=0;
        }
    }
    return temp;
}

int BFS()
{
    queue<Node> q;
    s.step=0;
    s.a=ca;
    s.b=0;
    s.c=0;
    flag[s.a][s.b][s.c]=1;
    q.push(s);

    while(!q.empty())
    {
        Node node=q.front();
        q.pop();
        if(node.a==n||node.b==n||node.c==n)
        {
            while(!q.empty()) q.pop();
            return node.step;
        }


            if(node.a!=0&&node.b<cb)
            {
                temp=transform(node,0);
                if(!flag[temp.a][temp.b][temp.c])
                {
                    q.push(temp);
                    flag[temp.a][temp.b][temp.c]=1;
                }
            }
            if(node.a!=0&&node.c<cc)
            {
                temp=transform(node,1);
                if(!flag[temp.a][temp.b][temp.c])
                {
                    q.push(temp);
                    flag[temp.a][temp.b][temp.c]=1;
                }
            }
            if(node.b!=0&&node.a<ca)
            {
                temp=transform(node,2);
                if(!flag[temp.a][temp.b][temp.c])
                {
                    q.push(temp);
                    flag[temp.a][temp.b][temp.c]=1;
                }
            }
            if(node.b!=0&&node.c<cc)
            {
                temp=transform(node,3);
                if(!flag[temp.a][temp.b][temp.c])
                {
                    q.push(temp);
                    flag[temp.a][temp.b][temp.c]=1;
                }
            }
            if(node.c!=0&&node.a<ca)
            {
                temp=transform(node,4);
                if(!flag[temp.a][temp.b][temp.c])
                {
                    q.push(temp);
                    flag[temp.a][temp.b][temp.c]=1;
                }
            }
            if(node.c!=0&&node.b<cb)
            {
                temp=transform(node,5);
                if(!flag[temp.a][temp.b][temp.c])
                {
                    q.push(temp);
                    flag[temp.a][temp.b][temp.c]=1;
                }
            }

    }
    return -1;
}

int main()
{
    while(~scanf("%d%d%d%d",&ca,&cb,&cc,&n))
    {
        for(int i=0;i<100;i++)
        {
            for(int j=0;j<100;j++)
            {
                for(int m=0;m<100;m++)
                {
                    flag[i][j][m]=0;
                }
            }
        }
        int ans=BFS();
        if(ans==-1)
        {
            printf("no\n");
        }
        else
        {
            printf("yes\n%d\n",ans);
        }
    }
}
