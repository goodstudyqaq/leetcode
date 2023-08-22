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
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = words.size();
        int m = words[0].size();

        map<int, int>  M;
        map<string, int> IDX;
        int idx = 0;
        for (int i = 0; i < n; i++) {
            if (IDX.count(words[i]) == 0) {
                IDX[words[i]] = idx++;
            }
            int the_dix = IDX[words[i]];
            M[the_dix]++;
        }
        vector<int> ans;
        int sz = s.size();
        for (int i = 0; i < m; i++) {
            map<int, int> now = M;
            if (i + m * n - 1 >= sz) break;
            for (int j = 0; j < n; j++) {
                auto it = s.substr(i + j * m, m);
                int tmp;
                if (IDX.count(it) == 0) tmp = -1;
                else tmp = IDX[it];
                now[tmp]--;
                if (now[tmp] == 0) {
                    now.erase(tmp);
                }
            }
            int now_idx = i;
            while (now_idx + m * n - 1 < sz) {
                if (now.size() == 0) {
                    ans.push_back(now_idx);
                }
                if (now_idx + m * (n + 1) - 1 >= sz) break;
                auto it = s.substr(now_idx, m);
                int tmp;
                if (IDX.count(it) == 0) tmp = -1;
                else tmp = IDX[it];
                now[tmp]++;
                if (now[tmp] == 0) now.erase(tmp);
                it = s.substr(now_idx + m * n, m);
                if (IDX.count(it) == 0) tmp = -1;
                else tmp = IDX[it];
                now[tmp]--;
                if (now[tmp] == 0) now.erase(tmp);
                now_idx += m;
            }
        }
        return ans;

        
    }
};