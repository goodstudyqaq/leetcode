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
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> sum(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                sum[i][j] = matrix[i][j];
                if (i - 1 >= 0) sum[i][j] += sum[i - 1][j];
                if (j - 1 >= 0) sum[i][j] += sum[i][j - 1];
                if (i - 1 >= 0 && j - 1 >= 0) sum[i][j] -= sum[i - 1][j - 1];
            }
        }

        auto get_sum = [&](int x1, int y1, int x2, int y2) {
            int res = sum[x2][y2];
            if (x1 - 1 >= 0) res -= sum[x1 - 1][y2];
            if (y1 - 1 >= 0) res -= sum[x2][y1 - 1];
            if (x1 - 1 >= 0 && y1 - 1 >= 0) res += sum[x1 - 1][y1 - 1];
            return res;
        };

        vector<int> sum1(m);
        const int inf = numeric_limits<int>::max() / 2;
        int ans = -inf;
        for (int r1 = 0; r1 < n; r1++) {
            for (int r2 = r1; r2 < n; r2++) {
                for (int j = 0; j < m; j++) {
                    sum1[j] = get_sum(r1, j, r2, j);
                    if (j - 1 >= 0) sum1[j] += sum1[j - 1];
                }
                set<int> S;
                for (int j = 0; j < m; j++) {
                    int val = sum1[j];
                    if (val <= k) {
                        ans = max(ans, val);
                    }

                    int x = val - k;
                    auto it = S.lower_bound(x);
                    if (it != S.end()) {
                        ans = max(ans, val - *it);
                    }
                    S.insert(val);
                }
            }
        }
        return ans;
    }
};