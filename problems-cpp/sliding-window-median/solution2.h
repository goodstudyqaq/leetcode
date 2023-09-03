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

class DualHeap {
    int k;
    priority_queue<int> small;
    priority_queue<int, vector<int>, greater<int>> large;
    unordered_map<int, int> count;
    int small_size, large_size;

    template <typename T>
    void prune(T& heap) {
        while (heap.size()) {
            int val = heap.top();
            if (count.count(val)) {
                count[val]--;
                heap.pop();

                if (count[val] == 0) {
                    count.erase(val);
                }
            } else {
                break;
            }
        }
        make_balance();
    }

    void make_balance() {
        if (small_size > large_size + 1) {
            large.push(small.top());
            small.pop();
            small_size--;
            large_size++;
            prune(small);
        } else if (small_size < large_size) {
            small.push(large.top());
            large.pop();
            small_size++;
            large_size--;
            prune(large);
        }
    }

   public:
    DualHeap(int _k) {
        k = _k;
        small_size = 0, large_size = 0;
    }
    void insert(int val) {
        if (small.size() == 0 || small.top() >= val) {
            small.push(val);
            small_size++;
        } else {
            large.push(val);
            large_size++;
        }
        make_balance();
    }

    void erase(int val) {
        count[val]++;
        if (val <= small.top()) {
            small_size--;
            if (small.top() == val) {
                prune(small);
            }
        } else {
            large_size--;
            if (large.top() == val) {
                prune(large);
            }
        }
        make_balance();
    }

    double getMedian() {
        if (k % 2)
            return small.top();
        else
            return (1.0 * small.top() + large.top()) / 2.0;
    }
};

class Solution {
   public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        DualHeap dh(k);
        for (int i = 0; i < k; ++i) {
            dh.insert(nums[i]);
        }
        vector<double> ans = {dh.getMedian()};
        for (int i = k; i < nums.size(); ++i) {
            dh.insert(nums[i]);
            dh.erase(nums[i - k]);
            ans.push_back(dh.getMedian());
        }
        return ans;
    }
};