#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

struct node
{
    int data,height;
    node *lchild;
    node *rchild;
};
int getHeight(node * root)
{
    if(root==NULL)
        return 0;
    return root->height;
}
void updateHeight(node * root)
{
    root->height=max(getHeight(root->lchild),getHeight(root->rchild))+1;
}
int getBalanceFactor(node * root)
{
    return getHeight(root->lchild)-getHeight(root->rchild);
}
void R(node * &root)
{
    node * temp=root->lchild;
    root->lchild=temp->rchild;
    temp->rchild=root;
    updateHeight(root);
    updateHeight(temp);
    root=temp;
}
void L(node * &root)
{
    node * temp=root->rchild;
    root->rchild=temp->lchild;
    temp->lchild=root;
    updateHeight(root);
    updateHeight(temp);
    root=temp;
}
void insert(node * &root, int x)
{
    if(root==NULL)
    {
        node * temp=new node;
        temp->data=x;
        temp->height=1;
        temp->rchild=temp->lchild=NULL;
        root=temp;
        return ;
    }
    if(x>root->data)
    {
        insert(root->rchild,x);
        updateHeight(root);
        if(getBalanceFactor(root)==-2)
        {
            if(getBalanceFactor(root->rchild)==-1)
            {
                L(root);
            }
            else if(getBalanceFactor(root->rchild)==1)
            {
                R(root->rchild);
                L(root);
            }
        }
    }
    else
    {
        insert(root->lchild,x);
        updateHeight(root);
        if(getBalanceFactor(root)==2)
        {
            if(getBalanceFactor(root->lchild)==-1)
            {
                L(root->lchild);
                R(root);
            }
            else if(getBalanceFactor(root->lchild)==1)
            {
                R(root);
            }
        }
    }
}
int search(node * root ,int x)
{
    if(root==NULL)
        return 0;
    if(root->data==x)
        return 1;
    else if(root->data<x)
        search(root->rchild,x);
    else
        search(root->lchild,x);
}
int main()
{
    int n,k,data;
    while(~scanf("%d %d",&n,&k))
    {
        node * root=NULL;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&data);
            insert(root,data);
        }
        for(int i=0;i<k;++i)
        {
            scanf("%d",&data);
            printf("%d ",search(root,data));
        }
        printf("\n");
    }
    return 0;
}