#include<cstdio>
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
struct Node{
    int sum;
    int begin;
    int end;
    int num;
};
bool visited[10010]={false};
int dp[10010];
int dp_end[10010];
int dp_num[10010];
int k;
vector<int> input;
int cmp(Node a,Node b)
{
    if(a.sum!=b.sum) return a.sum>b.sum;
    return a.num<b.num;
}
Node DFS(int s)
{
    int num=0;
    vector<Node> n;
    Node wei;
    wei.sum=input[s];
    wei.begin=input[s];
    wei.end=input[s];
    wei.num=1;
    n.push_back(wei);
    for(int i=s+1;i<k;i++)
    {
        if(visited[i])
        {
            Node temp=n[num];
            temp.end=dp_end[i];
            temp.sum+=dp[i];
            temp.num+=dp_num[i];
            n.push_back(temp);
            break;
        }
        else
        {
            Node temp=n[num];
            temp.end=input[i];
            temp.sum+=input[i];
            temp.num++;
            n.push_back(temp);
            num++;
        }
    }
    sort(n.begin(),n.begin()+n.size(),cmp);
    visited[s]= true;
    dp[s]=n[0].sum;
    dp_end[s]=n[0].end;
    dp_num[s]=n[0].num;
    return n[0];
}

int main()
{
    cin>>k;
    for(int i=0;i<k;i++)
    {
        int num;
        cin>>num;
        input.push_back(num);
    }
    Node max;
    max.sum=-1;
    for(int i=k-1;i>=0;i--)
    {
        Node temp=DFS(i);
        if(input[i]<0) continue;
        if(temp.sum>=max.sum)
        {
            max=temp;
        }
    }
    if(max.sum<0)
    {
        printf("0 %d %d",input[0],input[k-1]);
    }
    else
    {
        printf("%d %d %d",max.sum,max.begin,max.end);
    }
    return 0;
}
