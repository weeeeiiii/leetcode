#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;

queue<int> q;
int sum=0;
int level=0;
bool visited[10000]={false};
int main()
{
    int num;
    cin>>num;
    for(int i=0;i<num;i++)
    {
        int number;
        cin>>number;
        q.push(number);
    }
    while(!q.empty())
    {
        int n=q.front();
        q.pop();
        if(n>level)
        {
            sum=sum+(n-level)*6+5;
            level=n;
            continue;
        }
        else if(n<level)
        {
            sum=sum+(level-n)*4+5;
            level=n;
            continue;
        }
        else sum+=5;
    }
    printf("%d",sum);
    return 0;
}