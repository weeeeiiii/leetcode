#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

struct Node{
    string time;
    int in_time;
    int minute;
    int start;
    int end;
    int number;
};

queue<Node> q[100];
queue<Node> q2;
vector<Node> v;
int N,K;

int cmp(Node a,Node b)
{
    return a.time<b.time;
}

float renshu=0;
float sum=0;
int now_time=28800;
void progress()
{
    vector<int> a;
    for(int i=0;i<K;i++)
    {
        if(q[i].empty()) continue;
        a.push_back(q[i].front().start+q[i].front().minute*60);
    }
    if(a.size()==0) return;
    sort(a.begin(),a.begin()+a.size());
    for(int i=0;i<K;i++)
    {
        if(q[i].empty()) continue;
        if((q[i].front().start+q[i].front().minute*60)==a[0])
        {
            v[q[i].front().number].end=q[i].front().start+q[i].front().minute*60;
            now_time=q[i].front().start+q[i].front().minute*60;
            q[i].pop();
            if(!q2.empty())
            {
                if(q2.front().in_time>now_time)
                {
                    q2.front().start=q2.front().in_time;
                    v[q2.front().number].start=q2.front().in_time;
                }
                else
                {
                    q2.front().start=now_time;
                    v[q2.front().number].start=now_time;
                }
                q[i].push(q2.front());
                q2.pop();
            }
            break;
        }
    }
    return;
}
int main()
{
    cin>>N>>K;
    for(int i=0;i<N;i++)
    {
        Node temp;
        cin>>temp.time>>temp.minute;
        v.push_back(temp);
    }
    sort(v.begin(),v.begin()+N,cmp);
    for(int i=0;i<N;i++)
    {
        v[i].number=i;
        int xiaoshi=(v[i].time[0]-'0')*10+v[i].time[1]-'0';
        int fenzhon=(v[i].time[3]-'0')*10+v[i].time[4]-'0';
        int miao=(v[i].time[6]-'0')*10+v[i].time[7]-'0';
        v[i].in_time=xiaoshi*3600+fenzhon*60+miao;
    }
    int jishu=0;
    for(int i=0;i<N;i++)
    {
        if(jishu>=K) break;
        if(v[jishu].in_time<28800) v[jishu].start=28800;
        else v[jishu].start=v[jishu].in_time;
        q[i%K].push(v[jishu]);
        jishu++;
    }
    for(int i=jishu;i<N;i++)
    {
        q2.push(v[i]);
    }
    for(int i=0;i<N;i++)
    {
        progress();
    }
    for(int i=0;i<N;i++)
    {
        if(v[i].in_time<61200)
        {
            renshu++;
            sum+=v[i].start-v[i].in_time;
        }
    }
    printf("%.1f",sum/renshu/60.0);
    return 0;
}