#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
int m;
struct Node{
    string name;
    string in;
    string out;
};
vector<Node> v;
int cmp1(Node s1,Node s2)
{
    int num1,num2;
    num1=(s1.in[0]-'0')*10+s1.in[1]-'0';
    num2=(s2.in[0]-'0')*10+s2.in[1]-'0';
    if(num1!=num2) return num1<num2;
    num1=(s1.in[3]-'0')*10+s1.in[4]-'0';
    num2=(s2.in[3]-'0')*10+s2.in[4]-'0';
    if(num1!=num2) return num1<num2;
    num1=(s1.in[6]-'0')*10+s1.in[7]-'0';
    num2=(s2.in[6]-'0')*10+s2.in[7]-'0';
    return num1<num2;
}
int cmp2(Node s1,Node s2)
{
    int num1,num2;
    num1=(s1.out[0]-'0')*10+s1.out[1]-'0';
    num2=(s2.out[0]-'0')*10+s2.out[1]-'0';
    if(num1!=num2) return num1>num2;
    num1=(s1.out[3]-'0')*10+s1.out[4]-'0';
    num2=(s2.out[3]-'0')*10+s2.out[4]-'0';
    if(num1!=num2) return num1>num2;
    num1=(s1.out[6]-'0')*10+s1.out[7]-'0';
    num2=(s2.out[6]-'0')*10+s2.out[7]-'0';
    return num1>num2;
}

int main()
{
    cin>>m;
    for(int i=0;i<m;i++)
    {
        Node s;
        cin>>s.name>>s.in>>s.out;
        v.push_back(s);
    }
    sort(v.begin(),v.begin()+m,cmp1);
    cout<<v[0].name;
    printf(" ");
    sort(v.begin(),v.begin()+m,cmp2);
    cout<<v[0].name;
    return 0;
}