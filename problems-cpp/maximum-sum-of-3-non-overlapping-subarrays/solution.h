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
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> sum(n + 1);

        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }

        vector<vector<int>> dp(n + 2, vector<int>(4, 0));
        vector<vector<int>> mx(n + 2, vector<int>(4, 0));
        vector<vector<int>> choose(n + 2, vector<int>(4, 0));

        for (int j = 1; j <= 3; j++) {
            for (int i = n - k * j + 1; i >= 1; i--) {
                dp[i][j] = sum[i + k - 1] - sum[i - 1] + mx[i + k][j - 1];
                if (dp[i][j] >= mx[i + 1][j]) {
                    mx[i][j] = dp[i][j];
                    choose[i][j] = i;
                } else {
                    mx[i][j] = mx[i + 1][j];
                    choose[i][j] = choose[i + 1][j];
                }
            }
        }
        vector<int> ans;

        int nowi = 1;
        int nowj = 3;

        while (nowj != 0) {
            int c = choose[nowi][nowj];
            ans.push_back(c - 1);
            nowi = c + k;
            nowj--;
        }
        return ans;
    }
};