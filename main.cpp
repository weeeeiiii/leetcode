#include<iostream>
#include<string>
#include<stack>
#include<cstdio>

using namespace std;

int n;

int judge(string ch)
{
    stack<char> op;
    for(int i=0;i<ch.length();i++)
    {
        if(ch[i]=='('||ch[i]=='['||ch[i]=='{')
        {
            op.push(ch[i]);
        }
        else if(ch[i]==')'||ch[i]==']'||ch[i]=='}')
        {
            if(op.size()==0) return 0;
            if(ch[i]==')')
            {
                if(op.top()!='(') return 0;
                op.pop();
            }
            else if(ch[i]==']')
            {
                if(op.top()!='[') return 0;
                op.pop();
            }
            else if(ch[i]=='}')
            {
                if(op.top()!='{') return 0;
                op.pop();
            }
        }
    }
    if(op.size()!=0) return 0;
    return 1;
}

int main()
{
    string str;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        cin>>str;

        if(judge(str)==1)
        {
            printf("yes\n");
        }
        else printf("no\n");
    }
    return 0;
}





