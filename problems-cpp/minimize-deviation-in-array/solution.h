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
    int minimumDeviation(vector<int>& nums) {
        int n = nums.size();
        int p_mx = 1;
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2)
                nums[i] *= 2;
            p_mx = max(p_mx, nums[i] >> __builtin_ctz(nums[i]));
        }
        int mi = p_mx;
        vector<int> V;
        for (int i = 0; i < n; i++) {
            mi = min(mi, nums[i]);
            while (nums[i] / 2 >= p_mx) {
                nums[i] /= 2;
            }
            if (nums[i] >= p_mx)
                V.push_back(nums[i]);
        }
        sort(V.begin(), V.end());
        int ans = V.back() - mi;
        debug(V, mi, p_mx);
        for (int i = V.size() - 1; i > 0; i--) {
            mi = min(mi, V[i] / 2);
            ans = min(ans, V[i - 1] - mi);
        }
        return ans;
    }
};