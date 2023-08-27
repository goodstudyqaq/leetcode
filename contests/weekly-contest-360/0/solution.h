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
    int furthestDistanceFromOrigin(string moves) {
        int a = 0, b = 0;
        for (auto c : moves) {
            if (c == 'L') a--;
            else if (c == 'R')a++;
            else b++;
        }
        
        return abs(a) + b;
        
    }
};