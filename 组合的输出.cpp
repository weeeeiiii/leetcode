#include<stdio.h>
#include<set>

using namespace std;

int n, r, out[1000];
int flag[1000] = {0};

void DFS(int index, int x) {
    if (index == r) {
        for (int i = 0; i < r; i++) {
            printf("%d ", out[i]);
        }
        printf("\n");
        return;
    }

    for (int i = x; i <= n && index < r; i++) {
        if (flag[i]) continue;
        out[index] = i;
        flag[i] = 1;
        DFS(index + 1, i);
        flag[i] = 0;
    }
}

int main() {
    scanf("%d %d", &n, &r);
    DFS(0, 1);
    return 0;
}
