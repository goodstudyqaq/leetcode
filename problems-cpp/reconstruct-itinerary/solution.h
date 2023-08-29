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
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        map<string, vector<string>> V;
        for (auto it : tickets) {
            V[it[0]].push_back(it[1]);
        }
        for (auto it : V) {
            string key = it.first;
            sort(V[key].begin(), V[key].end());
        }

        vector<string> stk;
        map<string, int> cnt;

        function<void(string&)> dfs = [&](string &u) {
            debug(u);
            for (int &i = cnt[u]; i < V[u].size();) {
                i++;
                dfs(V[u][i - 1]);
            }
            stk.push_back(u);
        };
        string s = "JFK";
        dfs(s);
        reverse(stk.begin(), stk.end());
        return stk;
    }

};