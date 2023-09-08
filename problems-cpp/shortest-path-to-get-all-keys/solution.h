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
    int shortestPathAllKeys(vector<string>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        int key = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] >= 'a' && grid[i][j] <= 'z') {
                    key++;
                }
            }
        }
        debug(n, m);

        int LIMIT = 1 << key;
        queue<pair<int, pair<int, int>>> Q;
        auto dis = vect(inf<int>, n, m, LIMIT);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '@') {
                    Q.push({0, {i, j}});
                    dis[i][j][0] = 0;
                    break;
                }
            }
        }

        int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};

        while (!Q.empty()) {
            auto [status, loc] = Q.front();
            Q.pop();
            if (status == ((1 << key) - 1)) {
                return dis[loc.first][loc.second][status];
            }
            auto [x, y] = loc;

            for (int i = 0; i < 4; i++) {
                int x2 = x + d[i][0], y2 = y + d[i][1];
                if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m) {
                    int new_s;
                    if (grid[x2][y2] == '#')
                        continue;
                    else if (grid[x2][y2] == '.' || grid[x2][y2] == '@') {
                        new_s = status;
                    } else if (grid[x2][y2] >= 'a' && grid[x2][y2] <= 'z') {
                        new_s = status | (1 << (grid[x2][y2] - 'a'));
                    } else if (grid[x2][y2] >= 'A' && grid[x2][y2] <= 'Z') {
                        int it = grid[x2][y2] - 'A';
                        if (((status >> it) & 1) == 0) continue;
                        new_s = status;
                    }
                    if (dis[x2][y2][new_s] == inf<int>) {
                        dis[x2][y2][new_s] = dis[x][y][status] + 1;
                        Q.push({new_s, {x2, y2}});
                    }
                }
            }
        }
        return -1;
    }
};