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
    int minOperations(vector<int>& nums, int target) {
        int n = nums.size();
        int now = 0;
        int cnt = 0;
        map<int, int> M;
        long long all = 0;
        for (int i = 0; i < n; i++) {
            M[-nums[i]]++;
            all += nums[i];
        }
        
        if (all < target) {
            return -1;
        }
        
        auto check = [&]() {
            map<int, int> tmpM = M;
            int now = 0;
            for (auto it : tmpM) {
                int val = -it.first;
                int cnt = it.second;
                while (cnt && now + val <= target) {
                    now += val;
                    cnt--;
                }
                tmpM[-val] = cnt;
            }
            if (now == target) return true;
            
            int need = target - now;
            int choose = -1;
            for (auto it : tmpM) {
                int val = -it.first;
                int cnt = it.second;
                if (cnt > 0 && val > need) {
                    choose = val;
                }
            }
            
            M[-choose]--;
            M[-choose / 2] += 2;
            if (M[-choose] == 0) M.erase(-choose);
            return false;
        };
    
        int ans = 0;
        int idx = check();
        while (idx == false) {
            ans++;
            idx = check();
        }
        return ans;
        
        
    }
};