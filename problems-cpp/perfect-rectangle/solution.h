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

class CountIntervals {
    typedef pair<int, int> pii;

   public:
    set<pii> S;
    long long ans;
    CountIntervals() {
        S.clear();
        ans = 0;
    }

    bool add(int left, int right) {
        auto it = S.lower_bound({left, -1});  // 目的是想找到第一个包围 [left, right] 的区间。
        if (it != S.begin()) {
            if (prev(it)->second >= left) {
                it--;
            }
        }

        int L = left, R = right;
        bool flag = false;
        while (it != S.end()) {
            if (it->first > right) break;
            flag = true;
            L = min(L, it->first);
            R = max(R, it->second);
            ans -= it->second - it->first;
            it = S.erase(it);
        }
        S.insert({L, R});
        ans += R - L;
        return flag;
    }

    bool operator==(const CountIntervals& c) {
        return S == c.S;
    }
};

struct Event {
    int x, y, h, flag;
    bool operator<(const Event& e) const {
        return x < e.x;
    }
};

class Solution {
   public:
    bool isRectangleCover(vector<vector<int>>& r) {
        int n = r.size();
        vector<Event> e;
        for (int i = 0; i < n; i++) {
            int x = r[i][0], y = r[i][1], a = r[i][2], b = r[i][3];
            e.push_back((Event){x, y, b - y, 1});
            e.push_back((Event){a, y, b - y, -1});
        }
        sort(e.begin(), e.end());
        typedef pair<int, int> pii;

        int sz = e.size();
        int now = 0;

        auto check = [&](set<pii>& S) {
            int r = -1;
            for (auto it : S) {
                if (r != -1 && r != it.first) {
                    return false;
                }
                r = it.second;
            }
            return true;
        };

        while (now < sz) {
            debug(now);
            int go = now;
            while (go < sz && e[go].x == e[now].x) go++;
            if (now == 0) {
                // first time
                set<pii> S;
                CountIntervals s;
                long long sum = 0;
                for (int i = now; i < go; i++) {
                    int h1 = e[i].y;
                    int h2 = e[i].y + e[i].h;
                    S.insert({h1, h2});
                    s.add(h1, h2);
                    sum += h2 - h1;
                }
                if (check(S) == false || sum != s.ans) return false;
            } else {
                CountIntervals s1, s2;
                long long sum = 0;
                for (int i = now; i < go; i++) {
                    int h1 = e[i].y;
                    int h2 = e[i].y + e[i].h;
                    if (e[i].flag == 1) {
                        sum += h2 - h1;
                        s1.add(h1, h2);
                    } else {
                        s2.add(h1, h2);
                    }
                }
                if (go == sz) break;
                debug(s1.S, s2.S, sum, s1.ans);
                if (((s1 == s2) == false) || sum != s1.ans) return false;
            }
            now = go;
        }
        return true;
    }
};