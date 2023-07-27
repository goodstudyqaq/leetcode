#if __has_include("../utils/cpp/help.hpp")
#include "../utils/cpp/help.hpp"
#elif __has_include("../../utils/cpp/help.hpp")
#include "../../utils/cpp/help.hpp"
#else
#define debug(...) 42
#endif

class Solution {
   public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        debug(n, left, right);
        int ans = 0;
        sort(left.begin(), left.end());
        sort(right.begin(), right.end());
        if (left.size()) {
            ans = max(ans, left[left.size() - 1]);
        }
        if (right.size()) {
            ans = max(ans, n - right[0]);
        }
        return ans;
    }
};