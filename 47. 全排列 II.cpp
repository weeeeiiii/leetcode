#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> result;
public:
    void backtracking(vector<int> nums, vector<int> data, vector<bool> used) {
        if (nums.size() == data.size()) {
            result.push_back(data);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if(used[i]) continue;
            if (i > 0 && nums[i] == nums[i - 1] && !used[i-1]) continue;
            used[i]=true;
            data.push_back(nums[i]);
            backtracking(nums,data,used);
            used[i]=false;
            data.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        vector<bool> used(nums.size(),false);
        vector<int> data;
        backtracking(nums,data,used);
        return result;
    }
};