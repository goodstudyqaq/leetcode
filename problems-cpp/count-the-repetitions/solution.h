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
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int k = 0;
        int num = 0;
        int idx = 0;
        vector<pii> V;
        V.push_back({num, idx});
        unordered_map<int, int> M;
        M[0] = 0;
        auto work = [&](int &num, int &idx) {
            int sz = s1.size();
            for (int i = 0; i < sz; i++) {
                if (s1[i] == s2[idx]) {
                    idx = (idx + 1) % s2.size();
                    if (idx == 0) {
                        num++;
                    }
                }
            }
        };
        int cycle_status;
        while (true) {
            k++;
            work(num, idx);
            if (M.count(idx)) {
                cycle_status = idx;
                break;
            }
            M[idx] = k;
            V.push_back({num, idx});
        }
        // k 轮 有 num 个 s2 no
        debug(k, num, V, cycle_status);
        if (n1 < k) {
            int have = V[n1].first;
            return have / n2;
        } else {
            int t = M[cycle_status];
            int have = V[t].first;
            int cycle = k - t;
            int one_num = num - have;
            n1 -= t;
            int times = n1 / cycle * one_num;
            times += have;
            debug(times);
            int times_have = n1 % cycle;
            auto it = V[t + times_have];
            times += it.first - V[t].first;
            return times / n2;
        }
    }
};