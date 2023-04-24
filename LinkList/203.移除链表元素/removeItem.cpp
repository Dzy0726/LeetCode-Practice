/*** 
 * @Author: Zhenyu Dong
 * @Date: 2023-04-24 17:21:35
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2023-04-24 17:25:49
 * @FilePath: /203.移除链表元素/removeItem.cpp
 * @Description: 
 * @
 * @Copyright (c) by Zhenyu Dong, All Rights Reserved. 
 */



class Solution {
public:
    struct ListNode{
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };
    
    ListNode* removeElements(ListNode* head, int val) {
        ListNode * vir = new ListNode();
        vir->next = head;
        ListNode * tmp = vir;
        while (tmp->next) {
            if(tmp->next->val == val) {
                ListNode * del = tmp->next;
                tmp->next = del->next;
                delete del;
            } else {
                tmp = tmp->next;
            }
        }
        head = vir->next;
        delete vir;
        return head;
    }
};