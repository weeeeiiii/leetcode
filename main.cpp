#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

int ca,cb,n;
int out[10000+50]={0};
int out_0[200][1000];
int length[200]={0};
int num=0;
int flag[105][105]={0};
struct Node{
    int v;       //目前的体积
}node_a,node_b;

void BFS(int index,Node a,Node b)
{
    if(b.v==n)
    {
        length[num++]=index;
        for(int i=0;i<index;i++)
        {
            out_0[num-1][i]=out[i];
        }
        return;
    }

    Node a1=a,b1=b;
    for(int i=1;i<=6;i++)
    {
        if(flag[a.v][b.v]) continue;
        if(i==1&&a.v<ca)
        {
            a1.v = ca;
            out[index] = i;
            flag[a.v][b.v]=1;
            BFS(index + 1, a1, b);
        }
        if(i==2&&b.v<cb)
        {
            b1.v=cb;
            out[index]=i;
            flag[a.v][b.v]=1;
            BFS(index+1,a,b1);
        }
        if(i==3&&a.v>0)
        {
            a1.v=0;
            out[index]=i;
            flag[a.v][b.v]=1;
            BFS(index+1,a1,b);
        }
        if(i==4&&b.v>0)
        {
            b1.v=0;
            out[index]=i;
            flag[a.v][b.v]=1;
            BFS(index+1,a,b1);
        }
        if(i==5&&a.v>0&&b.v<cb)
        {
            if(a.v+b.v>cb)
            {
                a1.v=a.v+b.v-cb;
                b1.v=cb;
            } else
            {
                a1.v=0;
                b1.v=a.v+b.v;
            }
            out[index]=i;
            flag[a.v][b.v]=1;
            BFS(index+1,a1,b1);
        }
        if(i==6&&b.v>0&&a.v<ca)
        {
            if(a.v+b.v>ca)
            {
                a1.v=ca;
                b1.v=b.v+a.v-ca;
            } else{
                b1.v=0;
                a1.v=a.v+b.v;
            }
            out[index]=i;
            flag[a.v][b.v]=1;
            BFS(index+1,a1,b1);
        }
        flag[a.v][b.v]=0;
    }
}
int main()
{
    scanf("%d%d%d",&ca,&cb,&n)==3;
    int tag=0;
    while(1)
    {
        if(tag!=0)
        {
            printf("\n");
        }
        node_a.v=0;
        node_b.v=0;

        num=0;
        for(int i=0;i<10000+50;i++)
        {
            out[i]=0;
        }
        for(int i=0;i<200;i++)
        {
            length[i]=0;
        }
        for(int i=0;i<200;i++)
        {
            for(int j=0;j<1000;j++)
            {
                out_0[i][j]=0;
            }
        }
        for(int i=0;i<105;i++)
        {
            for(int j=0;j<105;j++)
            {
                flag[i][j]=0;
            }
        }

        BFS(0,node_a,node_b);
        int min=0;

        for(int i=1;i<200;i++)
        {
            if(length[min]>length[i]&&length[i]!=0)
            {
                min=i;
            }
        }

        for(int i=0;i<length[min];i++)
        {
            if(out_0[min][i]==1) printf("fill A\n");
            else if(out_0[min][i]==2) printf("fill B\n");
            else if(out_0[min][i]==3) printf("empty A\n");
            else if(out_0[min][i]==4) printf("empty B\n");
            else if(out_0[min][i]==5) printf("pour A B\n");
            else if(out_0[min][i]==6) printf("pour B A\n");
        }
        printf("success");
        tag=1;
        if(scanf("%d%d%d",&ca,&cb,&n)==3) continue;
        else break;
    }
    return 0;
}
