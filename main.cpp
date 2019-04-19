#include<cstdio>
#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

struct Node2{
    string shijian;
    string zhuantai;
};

struct Node{
  string name;
  vector<Node2> jilu;
};

vector<Node> all;
int monney[24];

int cmp_name(Node a,Node b)
{
    return a.name<b.name;
}
int cmp_shijian(Node2 a,Node2 b)
{
    return a.shijian<b.shijian;
}

vector<float> jisuan(string a,string b)
{
    vector<float> sum;
    float total=0;
    int tianshu=(a[3]-'0')*10+a[4]-'0';
    int xiaoshi=(a[6]-'0')*10+a[7]-'0';
    int fenzhon=(a[9]-'0')*10+a[10]-'0';
    int n=tianshu*1440+xiaoshi*60+fenzhon;
    tianshu=(b[3]-'0')*10+b[4]-'0';
    xiaoshi=(b[6]-'0')*10+b[7]-'0';
    fenzhon=(b[9]-'0')*10+b[10]-'0';
    int m=tianshu*1440+xiaoshi*60+fenzhon;
    sum.push_back(m-n);
    xiaoshi=(a[6]-'0')*10+a[7]-'0';
    fenzhon=(a[9]-'0')*10+a[10]-'0';
    int all_minute=0;
    while(all_minute<m-n)
    {
        total+=monney[xiaoshi];
        all_minute++;
        fenzhon++;
        if(fenzhon>=60)
        {
            fenzhon=0;
            xiaoshi+=1;
            if(xiaoshi>23) xiaoshi=0;
        }
    }
    total=total/100;
    sum.push_back(total);
    return sum;
}

void progress(Node a)
{
    float sum=0;
    vector<Node2> temp=a.jilu;
    while(1)
    {
        if(temp.size()<2) return;
        if((temp[0].zhuantai=="on-line"&&temp[1].zhuantai=="off-line")||temp.size()<2)  //找到符合的匹配
        {
            break;
        }
        else
        {
            temp.erase(temp.begin());
        }
    }
    if(temp.size()<2) return;
    vector<float> n=jisuan(temp[0].shijian,temp[1].shijian);
    sum+=n[1];
    cout<<a.name<<' '<<temp[0].shijian[0]<<temp[0].shijian[1]<<endl;
    temp[0].shijian.erase(temp[0].shijian.begin(),temp[0].shijian.begin()+3);
    temp[1].shijian.erase(temp[1].shijian.begin(),temp[1].shijian.begin()+3);
    cout<<temp[0].shijian<<' '<<temp[1].shijian;
    printf(" %d $%.2f\n",int(n[0]),n[1]);
    temp.erase(temp.begin());
    temp.erase(temp.begin());
    while(temp.size()>=2)
    {
        while(1)
        {
            if((temp[0].zhuantai=="on-line"&&temp[1].zhuantai=="off-line")||temp.size()<2)  //找到符合的匹配
            {
                break;
            }
            else
            {
                temp.erase(temp.begin());
            }
        }
        if(temp.size()<2) break;
        vector<float> n=jisuan(temp[0].shijian,temp[1].shijian);
        sum+=n[1];
        temp[0].shijian.erase(temp[0].shijian.begin(),temp[0].shijian.begin()+3);
        temp[1].shijian.erase(temp[1].shijian.begin(),temp[1].shijian.begin()+3);
        cout<<temp[0].shijian<<' '<<temp[1].shijian;
        printf(" %d $%.2f\n",int(n[0]),n[1]);
        temp.erase(temp.begin());
        temp.erase(temp.begin());
    }
    printf("Total amount: $%.2f\n",sum);
    return ;
}

int main()
{
    for(int i=0;i<24;i++)
    {
        cin>>monney[i];
    }
    int number;
    cin>>number;
    for(int i=0;i<number;i++)
    {
        string temp_name;
        cin>>temp_name;
        int tag=0;
        for(int i=0;i<all.size();i++)
        {
            if(temp_name==all[i].name)    //用户已存在
            {
                tag=1;
                Node2 temp;
                cin>>temp.shijian>>temp.zhuantai;
                all[i].jilu.push_back(temp);
                break;
            }
        }
        if(tag==0)
        {
            Node temp;                        //用户不存在，添加该用户
            temp.name=temp_name;
            Node2 t;
            cin>>t.shijian>>t.zhuantai;
            temp.jilu.push_back(t);
            all.push_back(temp);
        }
    }
    sort(all.begin(),all.begin()+all.size(),cmp_name);
    for(int i=0;i<all.size();i++)
    {
        sort(all[i].jilu.begin(),all[i].jilu.begin()+all[i].jilu.size(),cmp_shijian);
    }

    for(int i=0;i<all.size();i++)
    {
        progress(all[i]);
    }
    return 0;
}