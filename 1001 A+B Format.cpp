#include<cstdio>
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
stack<int> s;

int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    int sum=a+b;
    if(sum==0)
    {
        printf("0");
        return 0;
    }
    if(sum<0)
    {
        printf("-");
        sum=-sum;
    }
    while(sum!=0)
    {
        int c=sum%10;
        s.push(c);
        sum=sum/10;
    }
    while(!s.empty())
    {
        int now=s.top();
        s.pop();
        printf("%d",now);
        if(!s.empty()&&s.size()%3==0)
        {
            printf(",");
        }
    }
    return 0;
}
