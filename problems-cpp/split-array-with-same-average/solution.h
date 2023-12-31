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

template <class T>
auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T& v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

class Solution {
   public:
    bool splitArraySameAverage(vector<int>& nums) {
        
        int n = nums.size();
        if (n == 1) return false;
        int m = n / 2;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
        }

        for (int i = 0; i < n; i++) {
            nums[i] = nums[i] * n - sum;
        }

        auto work = [&](int l, int r) -> unordered_set<int> {
            int len = r - l + 1;
            unordered_set<int> S;
            for (int i = 1; i < (1 << len) - 1; i++) {
                int val = 0;
                for (int j = l; j <= r; j++) {
                    if ((i >> (j - l)) & 1) {
                        val += nums[j];
                    }
                }
                S.insert(val);
            }
            return S;
        };

        auto s1 = work(0, m - 1);
        auto s2 = work(m, n - 1);
        debug(s1, s2, nums);
        if (s1.count(0)) return true;
        if (s2.count(0)) return true;

        for (auto it : s1) {
            if (s2.count(-it)) return true;
        }

        int sum1 = 0;
        for (int i = 0; i < m; i++) sum1 += nums[i];
        if (s2.count(-sum1)) return true;
        if (sum1 == 0) return true;
        sum1 = 0;
        for (int i = m; i < n; i++) sum1 += nums[i];
        if (s1.count(-sum1)) return true;
        if (sum1 == 0) return true;
        return false;
    }
};