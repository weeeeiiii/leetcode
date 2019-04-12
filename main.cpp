#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<float> v;
vector<float> w;
vector<float> t;
vector<float> l;
float sum=0;
int main()
{
    for(int i=0;i<3;i++)
    {
        float num;
        cin>>num;
        w.push_back(num);
        cin>>num;
        t.push_back(num);
        cin>>num;
        l.push_back(num);
    }
    for(int i=0;i<3;i++)
    {
        float num=max(w[i],t[i]);
        num=max(num,l[i]);
        v.push_back(num);
        if(num==w[i])
        {
            printf("W ");
        }
        else if(num==t[i])
        {
            printf("T ");
        }
        else if(num==l[i])
        {
            printf("L ");
        }
    }
    printf("%.2f",(v[0]*v[1]*v[2]*0.65-1)*2);
    return 0;
}