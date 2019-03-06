#include<cstdio>
#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;

typedef struct Node{
    char data;
    Node *lchild,*rchild;
}node;
char pre[50],in[50];

node* create(int preL,int preR,int inL,int inR)
{
    if(preL>preR) return NULL;


    node *root=(node*)malloc(sizeof(Node));
    root->data=pre[preL];
    int k;
    for(k=inL;k<=inR;k++)
    {
        if(in[k]==pre[preL])
            break;
    }

    int numleft=k-inL;

    root->lchild=create(preL+1,preL+numleft,inL,k-1);
    root->rchild=create(preL+numleft+1,preR,k+1,inR);
    return root;
}

void post(node* root)
{
    if(root!=NULL)
    {
        post(root->lchild);
        post(root->rchild);
        printf("%c",root->data);
    }
}

int main()
{
    while(cin>>pre>>in)
    {
        node *root=create(0,strlen(pre)-1,0,strlen(in)-1);
        post(root);
        printf("\n");
    }
    return 0;
}
