#include<cstdio>
#include<iostream>
#include<string>
#include<stack>
using namespace std;

string s;
stack<int> q;
int sum=0;
int main()
{
    cin>>s;
    for(int i=0;i<s.length();i++)
    {
        int num=s[i]-'0';
        sum+=num;
    }
    if(sum==0)
    {
        q.push(0);
    }
    while(sum!=0)
    {
        int gewei;
        gewei=sum%10;
        q.push(gewei);
        sum=sum/10;
    }
    while(!q.empty())
    {
        int num=q.top();
        q.pop();
        if(num==1)
        {
            printf("one");
        }
        else if(num==2)
        {
            printf("two");
        }
        else if(num==3)
        {
            printf("three");
        }
        else if(num==4)
        {
            printf("four");
        }
        else if(num==5)
        {
            printf("five");
        }
        else if(num==6)
        {
            printf("six");
        }
        else if(num==7)
        {
            printf("seven");
        }
        else if(num==8)
        {
            printf("eight");
        }
        else if(num==9)
        {
            printf("nine");
        }
        else if(num==0)
        {
            printf("zero");
        }
        if(q.size()!=0) printf(" ");
    }
    return 0;
}
