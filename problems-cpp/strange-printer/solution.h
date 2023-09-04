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
const int maxn = 100;
const int maxm = 26;
int dp[maxn][maxn][maxm];
int mi[maxn][maxn];

class Solution {
   public:
    int strangePrinter(string s) {
        int n = s.size();
        const int inf = numeric_limits<int>::max() / 2;
        int m = 26;
        for (int len = 1; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                if (len == 1) {
                    for (int k = 0; k < m; k++) {
                        if (s[l] - 'a' == k) {
                            dp[l][r][k] = 0;
                            mi[l][r] = k;
                        } else {
                            dp[l][r][k] = 1;
                        }
                    }
                } else {
                    mi[l][r] = 0;
                    for (int k = 0; k < m; k++) {
                        dp[l][r][k] = inf;
                        for (int p = l; p < r; p++) {
                            int tmp = min(dp[l][p][mi[l][p]] + (k != mi[l][p]), dp[l][p][k]);
                            int tmp2 = min(dp[p + 1][r][mi[p + 1][r]] + (k != mi[p + 1][r]), dp[p + 1][r][k]);
                            dp[l][r][k] = min(dp[l][r][k], tmp + tmp2);
                            if (dp[l][r][mi[l][r]] > dp[l][r][k]) {
                                mi[l][r] = k;
                            }
                        }
                    }
                }
            }
        }

        int ans = inf;
        for (int i = 0; i < m; i++) {
            ans = min(ans, dp[0][n - 1][i] + 1);
        }
        return ans;
    }
};