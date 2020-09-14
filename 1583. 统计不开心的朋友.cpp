class Solution {
    map<int, int> unhappy;
    vector<vector<int>> morefrined;

public:

    int unhappyFriends(int n, vector<vector<int>> &preferences, vector<vector<int>> &pairs) {
        morefrined.resize(n);

        for (int i = 0; i < pairs.size(); i++) {
            int child1 = pairs[i][0];
            int child2 = pairs[i][1];

            int number = 0;
            while (preferences[child1][number] != child2) {
                morefrined[child1].push_back(preferences[child1][number]);
                number++;
            }

            number = 0;
            while (preferences[child2][number] != child1) {
                morefrined[child2].push_back(preferences[child2][number]);
                number++;
            }
        }

        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                vector<int>::iterator result1 = find(morefrined[i].begin(), morefrined[i].end(), j);
                vector<int>::iterator result2 = find(morefrined[j].begin(), morefrined[j].end(), i);
                if (result1 != morefrined[i].end() && result2 != morefrined[j].end()) {
                    unhappy[i] = 1;
                    unhappy[j] = 1;
                }
            }
        }
        int number = 0;
        for (int i = 0; i < n; i++) {
            if (unhappy[i] == 1) number++;
        }
        return number;
    }
};