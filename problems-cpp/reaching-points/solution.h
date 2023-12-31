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
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (true) {
            if (tx == ty) {
                if (sx == tx && sy == ty) return true;
                return false;
            }
            if (tx < sx || ty < sy) return false;

            if (tx > ty) {
                if (sy == ty && (tx - sx) % ty == 0) return true;
                tx %= ty;
            } else {
                if (sx == tx && (ty - sy) % tx == 0) return true;
                ty %= tx;
            }
        }
        return false;
    }
};