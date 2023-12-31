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
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        int m = edges.size();
        vector<vector<pair<int, int>>> V(n);
        for (int i = 0; i < m; i++) {
            int u = edges[i][0], v = edges[i][1], cnt = edges[i][2];
            V[u].push_back({v, cnt});
            V[v].push_back({u, cnt});
        }

        const int inf = numeric_limits<int>::max() / 2;
        vector<int> dis(n, inf);
        priority_queue<pii, vector<pii>, greater<pii>> Q;
        dis[0] = 1;
        Q.push({dis[0], 0});

        while (!Q.empty()) {
            auto [d, u] = Q.top();
            Q.pop();
            for (int i = 0; i < V[u].size(); i++) {
                int v = V[u][i].first, cnt = V[u][i].second;
                if (dis[v] > dis[u] + cnt + 1) {
                    dis[v] = dis[u] + cnt + 1;
                    Q.push({dis[v], v});
                }
            }
        }
        debug(dis);
        int ans = 0;
        maxMoves++;
        for (int i = 0; i < m; i++) {
            int u = edges[i][0], v = edges[i][1], cnt = edges[i][2];
            int du = dis[u];
            int dv = dis[v];
            int left_cnt = 0, right_cnt = 0;
            if (maxMoves > du) {
                left_cnt = min(cnt, maxMoves - du);
            }
            if (maxMoves > dv) {
                right_cnt = min(cnt, maxMoves - dv);
            }
            ans += min(cnt, left_cnt + right_cnt);
        }

        for (int i = 0; i < n; i++) {
            if (dis[i] <= maxMoves) ans++;
        }

        return ans;
    }
};