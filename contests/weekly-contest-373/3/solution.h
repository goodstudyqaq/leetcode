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
    long long beautifulSubstrings(string s, int k) {
        int n = s.size();
        vector<int> sum(n);
        set<char> S{'a', 'e', 'i', 'o', 'u'};
        for (int i = 0; i < n; i++) {
            sum[i] = S.count(s[i]) ? 1 : -1;
            if (i) sum[i] += sum[i - 1];
        }
        vector<int> valid;
        for (int i = 0; i < k; i++) {
            if (i * i % k == 0) valid.push_back(i * 2);
        }
        vector<map<int, int>> M(2 * k);
        int mod = 2 * k;
        M[mod - 1][0] = 1;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int val = sum[i];
            for (int j = 0; j < valid.size(); j++) {
                int f = ((i - valid[j]) % mod + mod) % mod;
                ans += M[f][val];
            }
            M[i % mod][val]++;
        }
        return ans;
    }
};