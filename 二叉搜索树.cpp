#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct Node{
    int data;
    Node *lchild,*rchild;
};

vector<int> ori_pre,ori_in,root_pre,root_in;
string s;

void create(Node* &root,int data)
{
    if(root==NULL)
    {
        root=new Node;
        root->data=data;
        root->lchild=NULL;
        root->rchild=NULL;
        return;
    }

    if(data<root->data)
    {
        create(root->lchild,data);
    }
    else if(data>root->data)
    {
        create(root->rchild,data);
    }
    else return;
}

void pre(Node* root,vector<int> &v)
{
    if(root!=NULL)
    {
        v.push_back(root->data);
        pre(root->lchild,v);
        pre(root->rchild,v);
    }
    return;
}

void in(Node* root,vector<int> &v)
{
    if(root!=NULL)
    {
        in(root->lchild,v);
        v.push_back(root->data);
        in(root->rchild,v);
    }
    return;
}

int main()
{
    int n;
    scanf("%d",&n);
    while(n!=0)
    {
        Node* origin=NULL;
        cin>>s;
        for(int i=0;i<s.length();i++)
        {
            create(origin,s[i]-'0');
        }
        for(int m=0;m<n;m++)
        {
            cin>>s;
            Node *root=NULL;
            for(int i=0;i<s.length();i++)
            {
                create(root,s[i]-'0');
            }
            pre(origin,ori_pre);
            in(origin,ori_in);
            pre(root,root_pre);
            in(root,root_in);
            if(ori_pre==root_pre&&ori_in==root_in)
            {
                printf("YES\n");
            }
            else printf("NO\n");
            ori_pre.clear();
            ori_in.clear();
            root_pre.clear();
            root_in.clear();
        }
        scanf("%d",&n);
    }
    return 0;
}
