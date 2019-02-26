#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>
#include<map>
#include<string>

using namespace std;

struct node{
    double num;    //操作数
    char op;       //操作符
    bool flag;     //true为操作数，false为操作符
};

string str;
stack<node> s;
queue<node> q;
map<char,int> op;

void Change()      //将后缀表达式变为中缀表达式
{
    double num;
    node temp;
    for(int i=0;i<str.length();)
    {
        if(str[i]>='0'&&str[i]<='9')
        {
            temp.flag=true;
            temp.num=str[i]-'0';
            i++;
            while(i<str.length()&&str[i]>='0'&&str[i]<='9')
            {
                temp.num=temp.num*10+str[i]-'0';
                i++;
            }
            q.push(temp);
        } else{
            temp.flag=false;
            while(!s.empty()&&op[str[i]]<=op[s.top().op])
            {
                q.push(s.top());
                s.pop();
            }
            temp.op=str[i];
            s.push(temp);
            i++;
        }
    }
    while(!s.empty())
    {
        q.push(s.top());
        s.pop();
    }
}

double Cal()        //计算后缀表达式
{
    double temp1,temp2;
    node cur,temp;
    while(!q.empty())
    {
        cur=q.front();
        q.pop();
        if(cur.flag==true) s.push(cur);
        else
        {
            temp2=s.top().num;
            s.pop();
            temp1=s.top().num;
            s.pop();
            temp.flag=true;
            if(cur.op=='+') temp.num=temp1+temp2;
            else if(cur.op=='-') temp.num=temp1-temp2;
            else if(cur.op=='*') temp.num=temp1*temp2;
            else temp.num=temp1/temp2;
            s.push(temp);
        }
    }
    return s.top().num;
}

int main()
{
    op['+']=op['-']=1;
    op['*']=op['/']=2;
    while(getline(cin,str),str!="0")
    {
        for(string::iterator it=str.end();it!=str.begin();it--)
        {
            if(*it==' ') str.erase(it);
        }
        while(!s.empty()) s.pop();
        Change();
        printf("%.2f\n",Cal());
    }
    return 0;
}









