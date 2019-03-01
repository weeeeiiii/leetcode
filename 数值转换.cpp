#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int M=10;

int main()
{
    int a[M];
    for(int i=0;i<M;i++)
    {
        scanf("%d",a+i);
    }
    int min=0,max=0;
    for(int i=1;i<M;i++)
    {
        if(a[min]>a[i]) min=i;
    }
    swap(a[0],a[min]);
    for(int i=0;i<M;i++)
    {
        if(a[max]<a[i]) max=i;
    }
    swap(a[M-1],a[max]);

    for(int i=0;i<M;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
