#include<iostream>
#include<cstdio>
#include<stdlib.h>
using namespace std;

struct Node{
    int num;
    Node *next;
};

int main()
{
    Node *head1=(Node*)malloc(sizeof(Node));
    head1->num=0;
    head1->next=NULL;

    int m,n;
    scanf("%d",&m);
    Node *p=(Node*)malloc(sizeof(Node));
    head1->next=p;
    for(int i=0;i<m;i++)
    {
        if(p==NULL) p=(Node*)malloc(sizeof(Node));
        scanf("%d",&(p->num));
        p->next=(Node*)malloc(sizeof(Node));
        p=p->next;
    }

    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        if(p==NULL) p=(Node*)malloc(sizeof(Node));
        scanf("%d",&(p->num));
        p->next=(Node*)malloc(sizeof(Node));
        p=p->next;
    }
    p=head1->next;
    for(int i=0;i<m+n;i++)
    {
        printf("%d ",p->num);
        p=p->next;
    }
    return 0;
}