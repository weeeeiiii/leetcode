#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


class Solution {
    vector<vector<int>> result;
public:
    void DFS(vector<int> nums, vector<int> now, int position) {
        if (position == nums.size()) {
            result.push_back(now);
            return;
        }
        DFS(nums, now, position + 1);
        now.push_back(nums[position]);
        DFS(nums, now, position + 1);
    }

    vector<vector<int>> subsets(vector<int> &nums) {
        vector<int> now;
        DFS(nums, now, 0);
        return result;
    }
};