#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

int n,m;
struct Node{
    string xuehao;
    int c,m,e;
    int a;
    int mingci;
};
vector<Node> v;
char fanshi;
void paixu()
{
    int ming=1;
    v[0].mingci=1;
    int shiji=2;
    for(int i=1;i<n;i++)
    {
        if(fanshi=='a')
        {
            if(v[i].a==v[i-1].a)
            {
                v[i].mingci=ming;
            }
            else
            {
                v[i].mingci=shiji;
                ming=shiji;
            }
        }
        else if(fanshi=='c')
        {
            if(v[i].c==v[i-1].c)
            {
                v[i].mingci=ming;
            }
            else
            {
                v[i].mingci=shiji;
                ming=shiji;
            }
        }
        else if(fanshi=='m')
        {
            if(v[i].m==v[i-1].m)
            {
                v[i].mingci=ming;
            }
            else
            {
                v[i].mingci=shiji;
                ming=shiji;
            }
        }
        else if(fanshi=='e')
        {
            if(v[i].e==v[i-1].e)
            {
                v[i].mingci=ming;
            }
            else
            {
                v[i].mingci=shiji;
                ming=shiji;
            }
        }
        shiji++;
    }
}
int cmp(Node a,Node b)
{
    if(fanshi=='a')
    {
        return a.a>b.a;
    }
    else if(fanshi=='c')
    {
        return a.c>b.c;
    }
    else if(fanshi=='m')
    {
        return a.m>b.m;
    }
    else if(fanshi=='e')
    {
        return a.e>b.e;
    }
}
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        Node temp;
        cin>>temp.xuehao>>temp.c>>temp.m>>temp.e;
        temp.a=(temp.c+temp.m+temp.e)/3;
        v.push_back(temp);
    }
    for(int i=0;i<m;i++)
    {
        string s;
        cin>>s;
        int tag=0;
        for(int j=0;j<n;j++)
        {
            if(s==v[j].xuehao)
            {
                tag=1;
                break;
            }
        }
        if(tag==0)
        {
            printf("N/A\n");
            continue;
        }
        int min=n+1;
        char kemu='A';
        fanshi='a';
        sort(v.begin(),v.begin()+n,cmp);
        paixu();
        for(int i=0;i<n;i++)
        {
            if(s==v[i].xuehao&&min>v[i].mingci)
            {
                min=v[i].mingci;
                kemu='A';
                break;
            }
        }
        fanshi='c';
        sort(v.begin(),v.begin()+n,cmp);
        paixu();
        for(int i=0;i<n;i++)
        {
            if(s==v[i].xuehao&&min>v[i].mingci)
            {
                min=v[i].mingci;
                kemu='C';
                break;
            }
        }
        fanshi='m';
        sort(v.begin(),v.begin()+n,cmp);
        paixu();
        for(int i=0;i<n;i++)
        {
            if(s==v[i].xuehao&&min>v[i].mingci)
            {
                min=v[i].mingci;
                kemu='M';
                break;
            }
        }
        fanshi='e';
        sort(v.begin(),v.begin()+n,cmp);
        paixu();
        for(int i=0;i<n;i++)
        {
            if(s==v[i].xuehao&&min>v[i].mingci)
            {
                min=v[i].mingci;
                kemu='E';
                break;
            }
        }
        printf("%d %c\n",min,kemu);
    }
    return 0;
}
