#if __has_include("../utils/cpp/help.hpp")
#include "../utils/cpp/help.hpp"
#endif

class Solution {
   public:
    int longestSemiRepetitiveSubstring(string s) {
        int n = s.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int j = i + 1;
            int score = 0;
            while (j < n && score + (s[j - 1] == s[j]) <= 1) {
                score += (s[j - 1] == s[j]);
                j++;
            }
            ans = max(ans, j - i);
        }
        return ans;
    }
};