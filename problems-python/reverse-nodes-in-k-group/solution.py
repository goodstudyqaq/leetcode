"""
Code generated by https://github.com/goodstudyqaq/leetcode-local-tester
"""
try:
    from utils.python3.help import *
except ImportError:
    pass # In leetcode environment, we don't need to import the help file.

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        if k == 1:
            return head
        now = head
        n = 0
        while now:
            n += 1
            now = now.next
        if n // k == 0:
            return head
        
        rt = ListNode(next=head)
        now = rt

        for i in range(n // k):
            go = now.next
            go2 = go.next
            for j in range(k - 1):
                tmp = go2.next
                go2.next = go
                go = go2
                go2 = tmp
            tmp = now.next
            now.next = go
            tmp.next = go2
            now = tmp
        return rt.next
