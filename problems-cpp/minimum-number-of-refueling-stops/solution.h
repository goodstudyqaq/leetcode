/*
Code generated by https://github.com/goodstudyqaq/leetcode-local-tester
*/
#if __has_include("../utils/cpp/help.hpp")
#include "../utils/cpp/help.hpp"
#elif __has_include("../../utils/cpp/help.hpp")
#include "../../utils/cpp/help.hpp"
#else
#define debug(...) 42
#endif

class Solution {
   public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        stations.push_back({target, 0});
        int n = stations.size();

        if (startFuel >= target) {
            return 0;
        }

        int now_idx = 0;
        long long have = startFuel;

        int ans = 0;
        priority_queue<int> Q;

        while (true) {
            while (now_idx < n && stations[now_idx][0] <= have) {
                Q.push(stations[now_idx][1]);
                now_idx++;
            }

            if (now_idx == n) {
                return ans;
            }

            if (Q.size() == 0) {
                return -1;
            }

            int tmp = Q.top();
            Q.pop();
            ans++;
            have += tmp;
        }
        return 0;
    }
};