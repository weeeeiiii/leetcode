#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


class Solution {
    int maxn = 0;
public:
    void DFS(string s, string now, int position, map<string, int> mp, int number) {
        if (position == s.length()) {
            maxn = max(maxn, number);
            return;
        }
        now += s[position];
        if (mp[now] == 1) {
            //出现重复的了，必须往后继续添加
            DFS(s, now, position + 1, mp, number);
        } else {
            //没有出现重复的，选择截取
            mp[now] = 1;
            DFS(s, "", position + 1, mp, number + 1);
            if(number+s.length()-position-1>maxn)
            {
                //没有出现重复的，选择继续添加
                mp[now] = 0;
                DFS(s, now, position + 1, mp, number);
            }
        }
    }

    int maxUniqueSplit(string s) {
        map<string, int> mp;
        string now = "";
        DFS(s, now, 0, mp, 0);
        return maxn;
    }
};

int main()
{
    Solution solution;
    cout<<solution.maxUniqueSplit("ababccc");
    return 0;
}