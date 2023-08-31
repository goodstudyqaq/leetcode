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
    int trapRainWater(vector<vector<int>>& heightMap) {
        int n = heightMap.size();
        int m = heightMap[0].size();
        vector<vector<int>> water(n, vector<int>(m, -1));
        typedef pair<int, int> pii;
        typedef pair<int, pii> piii;
        priority_queue<piii, vector<piii>, greater<piii>> Q;
        for (int i = 0; i < n; i++) {
            water[i][0] = heightMap[i][0];
            Q.push({water[i][0], {i, 0}});
            water[i][m - 1] = heightMap[i][m - 1];
            Q.push({water[i][m - 1], {i, m - 1}});
        }
        for (int i = 0; i < m; i++) {
            water[0][i] = heightMap[0][i];
            Q.push({water[0][i], {0, i}});
            water[n - 1][i] = heightMap[n - 1][i];
            Q.push({water[n - 1][i], {n - 1, i}});
        }
        int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
        while (!Q.empty()) {
            auto it = Q.top();
            Q.pop();
            int val = it.first, x = it.second.first, y = it.second.second;
            for (int i = 0; i < 4; i++) {
                int x2 = x + d[i][0];
                int y2 = y + d[i][1];
                if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m && water[x2][y2] == -1) {
                    water[x2][y2] = max(heightMap[x2][y2], val);
                    Q.push({water[x2][y2], {x2, y2}});
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans += water[i][j] - heightMap[i][j];
            }
        }
        return ans;
    }
};