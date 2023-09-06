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
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        vector<int> a2 = arr;
        sort(a2.begin(), a2.end());

        int now = 0;
        int ans = 0;
        while (now < n) {
            multiset<int> S1, S2;
            int go = now;
            ans++;
            do {
                S1.insert(a2[go]);
                S2.insert(arr[go]);
                go++;
            } while (go < n && S1 != S2);
            now = go;
        }
        return ans;
    }
};