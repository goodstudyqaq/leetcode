"""
Code generated by https://github.com/goodstudyqaq/leetcode-local-tester
"""
try:
    from utils.python3.help import *
except ImportError:
    pass # In leetcode environment, we don't need to import the help file.

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        n = len(nums1)
        m = len(nums2)
        mid = (n + m - 1) // 2

        l = 0
        r = 0
        def work():
            nonlocal l, r
            v1 = nums1[l] if l < n else 1e9
            v2 = nums2[r] if r < m else 1e9
            if v1 < v2:
                l += 1
                return v1
            else:
                r += 1
                return v2
        
        for i in range(mid):
            work()
        if (n + m) % 2 == 1:
            return work()
        else:
            return (work() + work()) / 2.0
