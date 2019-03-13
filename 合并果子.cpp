#include<cstdio>
#include<queue>
#include<iostream>
using namespace std;

priority_queue<int,vector<int>,greater<int> >q;

int main()
{
    int n;
    int a[30010];
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        scanf("%d",a+i);
        q.push(a[i]);
    }

    int ans=0;
    int x,y;
    while(q.size()>1)
    {
        x=q.top();
        q.pop();
        y=q.top();
        q.pop();
        ans+=(x+y);
        q.push(x+y);
    }
    printf("%d",ans);
    return 0;
}
