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


class Solution {
   public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        int limit = inf<int>;
        auto dp = vect(-limit, n, k + 1, 2);
        dp[0][0][1] = -prices[0];
        dp[0][0][0] = 0;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j][0] = dp[i - 1][j][0];
                if (j - 1 >= 0) {
                    dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j - 1][1] + prices[i]);
                }
                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j][0] - prices[i]);
            }
        }

        int ans = 0;
        for (int i = 0; i <= k; i++) {
            ans = max(ans, dp[n - 1][i][0]);
        }
        return ans;

    }
};