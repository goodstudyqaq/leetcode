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
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        int mid = (n + m + 1) / 2;

        int l = 0, r = 0;
        int ans;

        auto work = [&]() {
            int v1 = l < n ? nums1[l] : 1e9;
            int v2 = r < m ? nums2[r] : 1e9;
            if (v1 < v2) {
                ans = nums1[l];
                l++;
            } else {
                ans = nums2[r];
                r++;
            }
        };

        while (mid--) {
            work();
                            }

        if ((n + m) % 2) return ans;
        int tmp = ans;
        work();
        return (tmp + ans) / 2.0;
    }
};