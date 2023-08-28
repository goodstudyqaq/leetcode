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
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        wordList.push_back(beginWord);
        int n = wordList.size();
        int s = n - 1, t = -1;
        for (int i = 0; i < n; i++) {
            if (wordList[i] == endWord) {
                t = i;
                break;
            }
        }
        if (t == -1) return {};

        vector<vector<int>> V(n);

        auto check = [&](int a, int b) {
            int cnt = 0;
            int sz = beginWord.size();
            for (int i = 0; i < sz; i++) {
                if (wordList[a][i] != wordList[b][i]) cnt++;
            }
            return cnt == 1;
        };

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (check(i, j)) {
                    V[i].push_back(j);
                    V[j].push_back(i);
                }
            }
        }

        queue<int> Q;
        const int inf = numeric_limits<int>::max() / 2;
        vector<int> d(n, inf);
        Q.push(s);
        d[s] = 0;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (auto v : V[u]) {
                if (d[v] == inf) {
                    d[v] = d[u] + 1;
                    Q.push(v);
                }
            }
        }

        if (d[t] == inf) return 0;
        return d[t] + 1; 

    }
};