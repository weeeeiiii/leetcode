#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
    typedef long long ll;
    ll maxn = -1;
public:

    int maxProductPath(vector<vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();
        ll max_dp[n][m];
        ll min_dp[n][m];
        memset(max_dp, 0, sizeof(0));
        memset(min_dp, 0, sizeof(0));
        max_dp[0][0] = grid[0][0];
        min_dp[0][0] = grid[0][0];
        for (int i = 1; i < n; i++) {
            max_dp[i][0] = max_dp[i - 1][0] * grid[i][0];
            min_dp[i][0] = min_dp[i - 1][0] * grid[i][0];
        }
        for (int j = 1; j < m; j++) {
            max_dp[0][j] = max_dp[0][j - 1] * grid[0][j];
            min_dp[0][j] = min_dp[0][j - 1] * grid[0][j];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                max_dp[i][j]=max({max_dp[i-1][j]*grid[i][j],max_dp[i][j-1]*grid[i][j],min_dp[i-1][j]*grid[i][j],min_dp[i][j-1]*grid[i][j]});
                min_dp[i][j]=min({max_dp[i-1][j]*grid[i][j],max_dp[i][j-1]*grid[i][j],min_dp[i-1][j]*grid[i][j],min_dp[i][j-1]*grid[i][j]});
            }
        }
        if(max_dp[n-1][m-1]<0) return -1;
        else return max_dp[n-1][m-1]%(1000000000+7);
    }
};