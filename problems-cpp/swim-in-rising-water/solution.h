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

struct DSU {
    std::vector<int> f;
    DSU(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        if (f[x] == x) {
            return x;
        }
        int y = leader(f[x]);
        f[x] = y;
        return f[x];
    }
    bool merge(int a, int b) {
        auto x = leader(a);
        auto y = leader(b);
        if (x == y) {
            return false;
        }
        f[x] = y;
        return true;
    }
};

typedef pair<int, int> pii;

class Solution {
   public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        if (n == 1 && m == 1) return grid[0][0];

        auto get_idx = [&](int x, int y) {
            return x * m + y;
        };

        auto get_loc = [&](int idx) -> pii {
            return {idx / m, idx % m};
        };

        vector<int> f(n * m);
        iota(f.begin(), f.end(), 0);
        sort(f.begin(), f.end(), [&](int a, int b) {
            auto [x1, y1] = get_loc(a);
            auto [x2, y2] = get_loc(b);
            return grid[x1][y1] < grid[x2][y2];
        });
        DSU dsu(n * m);

        int now = 0;
        int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
        while (dsu.leader(0) != dsu.leader(n * m - 1)) {
            debug(now);
            int idx = f[now];   
            auto [x, y] = get_loc(idx);
            for (int i = 0; i < 4; i++) {
                debug(i);
                int x2 = x + d[i][0], y2 = y + d[i][1];
                if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m && grid[x2][y2] < grid[x][y]) {
                    dsu.merge(idx, get_idx(x2, y2));
                } 
            }
            now++;
        }
        int idx = f[now - 1];
        auto [x, y] = get_loc(idx);
        return grid[x][y];
    }
};