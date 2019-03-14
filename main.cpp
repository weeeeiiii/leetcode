#include<iostream>
#include<algorithm>
#include<string>
#include<cstdio>
#include<vector>
#include<map>

using namespace std;

map<string,int> m;
map<string, int>::iterator it_1;
map<string, int>::iterator it_2;
map<string,int> name_to_bianhao;
vector<string> bianhao_to_name[2000];
vector<string> real_gang;
map<string,int> name_to_number;
int numgang=0,N,K;


int main()
{
    scanf("%d%d",&N,&K);
    for(int i=0;i<N;i++)
    {
        string temp1,temp2;
        int weight;
        cin>>temp1>>temp2>>weight;
        it_1=m.find(temp1);
        it_2=m.find(temp2);
        if(it_1==m.end()&&it_2==m.end())
        {
            numgang++;
            m[temp1]=m[temp2]=weight;
            name_to_bianhao[temp1]=numgang-1;
            name_to_bianhao[temp2]=numgang-1;
            bianhao_to_name[numgang-1].push_back(temp1);
            bianhao_to_name[numgang-1].push_back(temp2);
        }
        else if(it_1!=m.end()&&it_2==m.end())
        {
            int bianhao=name_to_bianhao[temp1];
            m[temp1]+=weight;
            m[temp2]=weight;
            name_to_bianhao[temp2]=bianhao;
            bianhao_to_name[bianhao].push_back(temp2);
        }
        else if(it_1==m.end()&&it_2!=m.end())
        {
            int bianhao=name_to_bianhao[temp2];
            m[temp1]=weight;
            m[temp2]+=weight;
            name_to_bianhao[temp1]=bianhao;
            bianhao_to_name[bianhao].push_back(temp1);
        }
        else if(it_1!=m.end()&&it_2!=m.end())
        {
            int num_1=name_to_bianhao[temp1];
            int num_2=name_to_bianhao[temp2];
            if(num_1<num_2)
            {
                for(vector<string>::iterator it=bianhao_to_name[num_2].begin();it!=bianhao_to_name[num_2].end();it++)
                {
                    string temp=*it;
                    name_to_bianhao[temp]=num_1;
                    bianhao_to_name[num_1].push_back(temp);
                }
                bianhao_to_name[num_2].clear();
            }
            else if(num_1>num_2)
            {
                for(vector<string>::iterator it=bianhao_to_name[num_1].begin();it!=bianhao_to_name[num_1].end();it++)
                {
                    string temp=*it;
                    name_to_bianhao[temp]=num_2;
                    bianhao_to_name[num_2].push_back(temp);
                }
                bianhao_to_name[num_1].clear();
            }
            m[temp1]+=weight;
            m[temp2]+=weight;
        }
    }

    int length=0;
    for(int i=0;i<numgang;i++)
    {
        int max=0;
        int num=0;
        int sum=0;
        string head;
        for(it_1=m.begin();it_1!=m.end();it_1++)
        {
            string name=it_1->first;
            int weight=it_1->second;
            if(name_to_bianhao[name]==i)
            {
                sum+=weight;
                num++;
                if(max<weight)
                {
                    max=weight;
                    head=name;
                }
            }
        }
        if(sum>(K*2)&&num>2)
        {
            length++;
            real_gang.push_back(head);
            name_to_number[head]=num;
        }
    }

    printf("%d",length);
    if(!real_gang.empty()) printf("\n");
    sort(real_gang.begin(),real_gang.begin()+length);
    for(int i=0;i<real_gang.size();i++)
    {
        cout<<real_gang[i]<<" "<<name_to_number[real_gang[i]];
        if(i<real_gang.size()-1) printf("\n");
    }
    return 0;
}