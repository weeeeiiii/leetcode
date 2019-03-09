#include<cstdio>
#include<iostream>
#include<vector>

using namespace std;

struct node{
    int data;
    node *left,*right;
};

void insert(node* &root,int data)
{
    if(root==NULL)
    {
        root=new node;
        root->data=data;
        root->left=root->right=NULL;
        return;
    }
    if(data<root->data) insert(root->left,data);
    else insert(root->right,data);
}

void preorder(node* root,vector<int> &vi)
{
    if(root==NULL) return;
    vi.push_back(root->data);
    preorder(root->left,vi);
    preorder(root->right,vi);
}


void preorderMirror(node* root,vector<int>&vi)
{
    if(root==NULL) return;
    vi.push_back(root->data);
    preorderMirror(root->right,vi);
    preorderMirror(root->left,vi);
}

void postorder(node* root,vector<int>&vi)
{
    if(root==NULL) return;
    postorder(root->left,vi);
    postorder(root->right,vi);
    vi.push_back(root->data);
}

void postorderMirror(node* root,vector<int>&vi)
{
    if(root==NULL) return ;
    postorderMirror(root->right,vi);
    postorderMirror(root->left,vi);
    vi.push_back(root->data);
}

vector<int> origin,pre,preM,post,postM;

int main()
{
    int n,data;
    node* root=NULL;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&data);
        origin.push_back(data);
        insert(root,data);
    }

    preorder(root,pre);
    preorderMirror(root,preM);
    postorder(root,post);
    postorderMirror(root,postM);
    if(origin==pre)
    {
        printf("YES\n");
        for(int i=0;i<post.size();i++)
        {
            printf("%d",post[i]);
            if(i<post.size()-1) printf(" ");
        }
    }

    else if(origin==preM)
    {
        printf("YES\n");
        for(int i=0;i<postM.size();i++)
        {
            printf("%d",postM[i]);
            if(i<postM.size()-1) printf(" ");
        }
    }

    else
    {
        printf("NO\n");
    }
    return 0;
}
