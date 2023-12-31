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

/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
   public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        int len = wordlist.size();
        vector<vector<int> > graph(len, vector<int>(len, 0));
        vector<bool> isValid(len, true);
        for (int i = 0; i < wordlist.size(); i++) {
            for (int j = i; j < wordlist.size(); j++) {
                int overlap = 0;
                for (int k = 0; k < 6; k++) {
                    if (wordlist[i][k] == wordlist[j][k]) {
                        overlap++;
                    }
                }
                graph[i][j] = overlap;
                graph[j][i] = overlap;
            }
        }

        while (true) {
            int mindata = INT_MAX;
            int minposition = -1;
            for (int i = 0; i < wordlist.size(); i++) {
                if (!isValid[i]) {
                    continue;
                }
                vector<int> count(7, 0);
                for (int j = 0; j < wordlist.size(); j++) {
                    count[graph[i][j]]++;
                }
                int currentmax = *max_element(count.begin(), count.end());
                // 取出每次的最坏结果
                if (currentmax < mindata) {
                    mindata = currentmax;
                    minposition = i;
                }
                // 让最坏的结果变得更好
            }
            int gap = master.guess(wordlist[minposition]);
            if (gap == 6) {
                return;
            }
            for (int i = 0; i < wordlist.size(); i++) {
                if (isValid[i] && graph[minposition][i] != gap) {
                    isValid[i] = false;
                }
            }
        }
    }
};
