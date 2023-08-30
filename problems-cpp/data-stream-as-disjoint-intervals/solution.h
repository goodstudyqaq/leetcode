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

    int ans = 0;
    set<pii> S;

   public:
    CountIntervals() {
        ans = 0;
        S.clear();
    }

    void add(int left, int right) {
        auto it = S.lower_bound({left, -1});  // 目的是想找到第一个包围 [left - 1, right + 1] 的区间。
        if (it != S.begin()) {
            if (prev(it)->second >= left - 1) {
                it--;
            }
        }

        int L = left, R = right;
        while (it != S.end()) {
            if (it->first > right + 1) break;
            L = min(L, it->first);
            R = max(R, it->second);
            ans -= it->second - it->first + 1;
            it = S.erase(it);
        }
        ans += R - L + 1;
        S.insert({L, R});
    }

    int count() {
        return ans;
    }

    pii get_interval(int idx) {
        auto it = S.lower_bound({idx + 1, -1});  // 写法很关键，找最后一个包围 idx 的区间可以这么写
        if (it == S.begin()) {
            return {-1, -1};
        }
        it--;
        if (it->second < idx) {
            return {-1, -1};
        }
        return *it;
    }

    vector<vector<int>> out() {
        vector<vector<int>> ans;
        for (auto it : S) {
            ans.push_back({it.first, it.second});
        }
        return ans;
    }

};


class SummaryRanges {
   public:
    CountIntervals ci;
    SummaryRanges() {
    }

    void addNum(int value) {
        ci.add(value, value);
    }

    vector<vector<int>> getIntervals() {
        return ci.out();
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */