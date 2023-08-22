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
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();

        vector<vector<int>> dp(n + 2, vector<int>(m + 2, -1));

        function<bool(int, int)> dfs = [&](int l1, int l2) -> bool {
            if (l1 > n && l2 > m) return true;
            if (l2 > m) return false;
            if (dp[l1][l2] != -1) return dp[l1][l2];

            if (l2 < m && p[l2] == '*') {
                char it = p[l2 - 1];
                bool flag = dfs(l1, l2 + 2);
                if (flag) return dp[l1][l2] = true;
                for (int i = l1 - 1; i < n; i++) {
                    if (s[i] == it || it == '.') {
                        flag = dfs(i + 2, l2 + 2);
                        if (flag) return dp[l1][l2] = true;
                    } else {
                        break;
                    }
                }               
                return dp[l1][l2] = false;
            } else {
                if (l1 > n) return false;
                if (s[l1 - 1] == p[l2 - 1] || p[l2 - 1] == '.') {
                    return dp[l1][l2] = dfs(l1 + 1, l2 + 1);
                } else {
                    return dp[l1][l2] = false;
                }

            }
        };
        return dfs(1, 1);
    }
};