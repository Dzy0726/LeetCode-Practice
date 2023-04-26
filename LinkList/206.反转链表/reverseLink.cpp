/*** 
 * @Author: Zhenyu Dong
 * @Date: 2023-04-26 10:49:53
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2023-04-26 11:29:38
 * @FilePath: /206.反转链表/reverseLink.cpp
 * @Description: 
 * @
 * @Copyright (c) 2023 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* p) : val(x), next(p) {}
    };
    
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* pre = new ListNode();
        ListNode* cur = new ListNode();
        ListNode* tmp = new ListNode();
        pre = nullptr;           
        cur = head;
        while(cur) {
           tmp = cur->next;
           cur->next = pre;
           pre = cur;
           cur = tmp;
        }
        return pre;
    }
};