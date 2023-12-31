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
    int movesToChessboard(vector<vector<int>>& board) {
        int n = board.size();

        int row_status = 0, col_status = 0;
        for (int i = 0; i < n; i++) {
            if (board[0][i]) {
                row_status |= (1 << i);
            }
            if (board[i][0]) {
                col_status |= (1 << i);
            }
        }

        int rev_row_status = ((1 << n) - 1) ^ row_status;
        int rev_col_status = ((1 << n) - 1) ^ col_status;

        int n1 = 0, n2 = 0;
        for (int i = 0; i < n; i++) {
            int rs = 0, cs = 0;
            for (int j = 0; j < n; j++) {
                if (board[i][j]) {
                    rs |= (1 << j);
                }
                if (board[j][i]) {
                    cs |= (1 << j);
                }
            }
            if (rs != row_status && rs != rev_row_status) return -1;
            if (cs != col_status && cs != rev_col_status) return -1;

            if (rs == row_status) n1++;
            if (cs == col_status) n2++;
        }

        // 1. check status whether is valid
        int ones = __builtin_popcount(row_status);
        if (abs(n - ones * 2) > 1) {
            return -1;
        }
        ones = __builtin_popcount(col_status);
        if (abs(n - ones * 2) > 1) {
            return -1;
        }

        // 2. check number
        if (abs(n - 2 * n1) > 1) {
            return -1;
        }

        if (abs(n - 2 * n2) > 1) {
            return -1;
        }
        auto work = [&](int status) {
            if (n % 2) {
                int one = __builtin_popcount(status);
                debug(one);
                if (one > n - one) {
                    // one
                    return __builtin_popcount(status & 0xAAAAAAAA);
                } else {
                    // zero
                    return  __builtin_popcount(status & 0x55555555);
                }
            } else {
                return min(__builtin_popcount(status & 0xAAAAAAAA), __builtin_popcount(status & 0x55555555));
            }
        };

        int ans = work(row_status) + work(col_status);
        return ans;
    }
};