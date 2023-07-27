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

typedef pair<int, int> pii;
class Solution {
   public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        vector<int> sz(n);
        vector<vector<bool>> mp(n, vector<bool>(n, 0));
        for (int i = 0; i < m; i++) {
            int u = edges[i][0] - 1, v = edges[i][1] - 1;
            sz[u]++;
            sz[v]++;
            mp[u][v] = mp[v][u] = 1;
        }

        vector<int> f(n);
        iota(f.begin(), f.end(), 0);
        sort(f.begin(), f.end(), [&](int x, int y) {
            return sz[x] < sz[y];
        });

        const int inf = 1e9;
        int ans = inf;
        for (int i = 0; i < m; i++) {
            int u = edges[i][0] - 1, v = edges[i][1] - 1;
            for (int j = 0; j < n; j++) {
                int idx = f[j];
                if (mp[idx][u] && mp[idx][v]) {
                    ans = min(ans, sz[u] + sz[v] + sz[idx] - 6);
                    break;
                }
            }
        }
        if (ans == inf) ans = -1;
        return ans;
    }
};