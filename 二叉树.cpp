#include <stdio.h>
int n,m,sum;
void BFS(int root){
    if(root>n)	return;
    sum++;
    BFS(2*root);
    BFS(2*root+1);
}
int main(){
    while(scanf("%d%d",&m,&n),m||n){
        sum=0;
        BFS(m);
        printf("%d\n",sum);
    }
    return 0;
}
