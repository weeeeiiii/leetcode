class Solution {
    map<int, int> mp;      //标记是否使用过该字母
    deque<deque<int>> xiabiao_s;
    deque<deque<int>> xiabiao_t;
public:
    bool isTransformable(string s, string t) {
        int nums1[10]={0}, nums2[10]={0};
        xiabiao_s.resize(10);
        xiabiao_t.resize(10);

        for (int i = 0; i < s.length(); i++) {
            nums1[s[i] - '0']++;
            xiabiao_s[s[i] - '0'].push_back(i);   //存放每个下标
        }
        for (int i = 0; i < t.length(); i++) {
            nums2[t[i] - '0']++;
            xiabiao_t[t[i] - '0'].push_back(i);   //存放每个下标
        }

        for (int i = 0; i < 10; i++) {
            if (nums1[i] != nums2[i]) return false;
        }

        for (int i = 0; i < t.length(); i++) {
            int ch = t[i] - '0';
            int minimum = xiabiao_s[ch][0];
            xiabiao_s[ch].pop_front(); // 把第一个下标去掉
            for (int i = 0; i < ch; i++) {
                if (xiabiao_s[i].size() != 0 && xiabiao_s[i][0] < minimum) return false;
            }
        }
        return true;
    }
};