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
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        vector<vector<int>> sum(n, vector<int>(m));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                sum[i][j] = matrix[i][j] - '0';
                if (i - 1 >= 0) {
                    sum[i][j] += sum[i - 1][j];
                }
                if (j - 1 >= 0) {
                    sum[i][j] += sum[i][j - 1];
                }
                if (i - 1 >= 0 && j - 1 >= 0) {
                    sum[i][j] -= sum[i - 1][j - 1];
                }
            }
        }

        auto get_sum = [&](int x1, int y1, int x2, int y2) {
            int res = sum[x2][y2];
            if (x1 - 1 >= 0) {
                res -= sum[x1 - 1][y2];
            }
            if (y1 - 1 >= 0) {
                res -= sum[x2][y1 - 1];
            }
            if (x1 - 1 >= 0 && y1 - 1 >= 0) {
                res += sum[x1 - 1][y1 - 1];
            }
            
            return res;
        };

        vector<int> sum2(m);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int mx = 0;
                int now = 0;
                int score = j - i + 1;
                while (now < m) {
                    int go = now;
                    while (go < m && get_sum(i, go, j, go) < score) {
                        go++;
                    }
                    int go2 = go;
                    while (go2 < m && get_sum(i, go2, j, go2) == score) {
                        go2++;
                    }
                    mx = max(mx, go2 - go);
                    now = go2;
                }
                ans = max(ans, score * mx);
                if (mx == 0) break;
            }
        }
        return ans;



    }
};