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
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        nums.resize(n + 1);
        for (int i = 0; i < n; i++) {
            int val = nums[i];
            if (val <= 0 || val > n) {
                nums[i] = -1;
            }
        }
        for (int i = 0; i < n; i++) {
            int val = nums[i];
            if (val == -1) continue;
            if (val == n + 1) continue;
            int now = val;
            while (now >= 1 && now <= n) {
                int go = nums[now];
                nums[now] = n + 1;
                now = go;
            }
        }
        // debug(nums);
        int now = 1;
        while (now <= n && nums[now] == n + 1) now++;
        return now;
    }
};