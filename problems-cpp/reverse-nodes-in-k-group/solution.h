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
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
   public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) return head;
        vector<ListNode*> V;
        ListNode* now = head;
        int n = 0;
        while (now != NULL) {
            now = now->next;
            n++;
        }
        if (n / k == 0) {
            return head;
        }
        ListNode* rt = new ListNode(-1);
        rt->next = head;
        now = rt;

        for (int i = 0; i < n / k; i++) {
            ListNode* go = now->next;
            ListNode* go2 = go->next;
            for (int j = 0; j < k - 1; j++) {
                debug(j);
                ListNode* tmp = go2->next;
                go2->next = go;
                go = go2;
                go2 = tmp;
            }
            ListNode *tmp = now->next;
            now->next = go;
            tmp->next = go2;
            now = tmp;
        }
        return rt->next;
    }
};