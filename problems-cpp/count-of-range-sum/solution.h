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
template <typename T>
struct Fenwick {
#define lowbit(x) x & -x
    const int n;
    vector<T> a;
    // [1, n]
    Fenwick(int n) : n(n), a(n + 1) {}
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    // [1, x]
    T query(int x) {
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }
};

class Solution {
   public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> sum(n + 1);
        vector<long long> x;
        x.push_back(0);
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + nums[i - 1];
            x.push_back(sum[i]);
        }
        sort(x.begin(), x.end());
        int x_num = unique(x.begin(), x.end()) - x.begin();
        Fenwick<long long> fen(x_num);
        int res = 0;
        for (int i = 1; i <= n; i++) {
            long long now = sum[i];
            if (sum[i] >= lower && sum[i] <= upper) res++;
            long long left = sum[i] - upper;
            long long right = sum[i] - lower;
            int idx = upper_bound(x.begin(), x.begin() + x_num, right) - x.begin();
            idx--;
            int idx2 = lower_bound(x.begin(), x.begin() + x_num, left) - x.begin();
            idx2--;
            int tmp = fen.query(idx + 1) - fen.query(idx2 + 1);
            res += tmp;
            idx = lower_bound(x.begin(), x.begin() + x_num, sum[i]) - x.begin();
            fen.add(idx + 1, 1);
        }
        return res;
    }
};