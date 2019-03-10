#include<cstdio>
#include<iostream>
using namespace std;

struct Node{
    int data;
    Node *lchild,*rchild;
};

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
    else if(data>root->data) create(root->rchild,data);
    else return;
}

void pre(Node* root)
{
    if(root!=NULL)
    {
        printf("%d ",root->data);
        pre(root->lchild);
        pre(root->rchild);
    }
    return;
}

void in(Node* root)
{
    if(root!=NULL)
    {
        in(root->lchild);
        printf("%d ",root->data);
        in(root->rchild);
    }
    return;
}

void post(Node* root)
{
    if(root!=NULL)
    {
        post(root->lchild);
        post(root->rchild);
        printf("%d ",root->data);
    }
    return;
}

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        Node *root=NULL;
        for(int i=0;i<n;i++)
        {
            int num;
            scanf("%d",&num);
            create(root,num);
        }
        pre(root);
        printf("\n");
        in(root);
        printf("\n");
        post(root);
        printf("\n");
    }
    return 0;
}