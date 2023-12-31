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
    vector<string> removeInvalidParentheses(string s) {
        string now = "";
        int n = s.size();

        int cnt = 0;
        int del = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') cnt++;
            else if (s[i] == ')') cnt--;
            if (cnt < 0) {
                del++;
                cnt = 0;
            }
        }
        del += cnt;
        unordered_set<string> ans;
        function<void(int, int)> dfs = [&](int idx, int score) {
            if (score < 0) return;
            if (idx - now.size() > del) return;
            if (idx == n) {
                if (score == 0) {
                    if (ans.size() == 0) {
                        ans.insert(now);
                    } else if (ans.begin()->size() < now.size()) {
                        ans.clear();
                        ans.insert(now);
                    } else if (ans.begin()->size() == now.size()) {
                        ans.insert(now);
                    }
                }
                return;
            }

            char it = s[idx];
            int flag = 0;
            if (it == '(')
                flag = 1;
            else if (it == ')')
                flag = -1;
            if (flag != 0) {
                dfs(idx + 1, score);
            }
            now += it;
            dfs(idx + 1, score + flag);
            now.pop_back();
        };
        dfs(0, 0);
        vector<string> res;
        for (auto it : ans) res.push_back(it);
        return res;
    }
};