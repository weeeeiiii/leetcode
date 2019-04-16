#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int sum=0;
struct Node{
    int shijian;
    int number;
    int kaishi;
    int jieshu;
};
int now_time;
queue<Node> q[21];
queue<Node> q2;
int N,M,K,Q;
bool visited[1010]={false};
Node all_time[1010];
void update()
{
    vector<int> v;
    int jishu=0;
    for(int i=0;i<N;i++)
    {
        if(!q[i].empty())
        {
            v.push_back(q[i].front().shijian);
            jishu++;
        }
    }
    if(v.size()==0) return;
    sort(v.begin(),v.begin()+jishu);
    sum+=v[0];
    for(int i=0;i<N;i++)
    {
        if(!q[i].empty())
        {
            if(q[i].front().shijian==v[0])
            {
                all_time[q[i].front().number].jieshu=sum;
                visited[q[i].front().number]=true;
                q[i].pop();
                if(!q[i].empty())
                {
                    all_time[q[i].front().number].kaishi=sum;
                }
                if(!q2.empty())
                {
                    q[i].push(q2.front());
                    q2.pop();
                }
            }
            else
            {
                q[i].front().shijian=q[i].front().shijian-v[0];
            }
        }
    }
}
int main()
{
    cin>>N>>M>>K>>Q;
    int number=0;
    for(int i=0;i<N*M;i++)
    {
        if(number>=K) break;
        Node temp;
        cin>>temp.shijian;
        temp.number=i+1;
        q[i%N].push(temp);
        number++;
    }
    for(int i=number;i<K;i++)
    {
        Node temp;
        temp.number=i+1;
        cin>>temp.shijian;
        q2.push(temp);
    }
    for(int i=0;i<K;i++)
    {
        update();
    }
    for(int i=0;i<Q;i++)
    {
        int num;
        cin>>num;
        if(all_time[num].kaishi>=540) printf("Sorry\n");
        else
        {
            printf("%02d:%02d\n",all_time[num].jieshu/60+8,all_time[num].jieshu%60);
        }
    }
    return 0;
}
