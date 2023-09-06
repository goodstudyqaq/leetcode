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
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        vector<int> to(n);

        for (int i = 0; i < n; i += 2) {
            int u = row[i], v = row[i + 1];
            to[u] = v;
            to[v] = u;
        }

        vector<int> vis(n);
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (vis[i] || vis[i + (i % 2 ? -1 : 1)]) continue;
            int now = i;
            int cir = 0;
            do {
                vis[now] = 1;
                cir++;
                int love = now % 2 ? now - 1 : now + 1;
                int go = to[love];
                now = go;
            } while (now != i);
            res += cir - 1;
        }
        return res;
    }
};