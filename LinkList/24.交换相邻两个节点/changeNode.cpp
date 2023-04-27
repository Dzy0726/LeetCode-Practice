/*** 
 * @Author: Zhenyu Dong
 * @Date: 2023-04-27 15:14:03
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2023-04-27 15:33:22
 * @FilePath: /24.交换相邻两个节点/changeNode.cpp
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
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };

    ListNode* swapPairs(ListNode* head) {
        ListNode * dummyHead = new ListNode();
        dummyHead->next = head;
        ListNode * cur = new ListNode();
        cur = dummyHead;
        while(cur->next && cur->next->next) {
            ListNode * tmp = cur->next;
            ListNode * tmp1 = cur->next->next->next;
            cur->next = tmp->next;
            cur->next->next = tmp;
            tmp->next = tmp1;
            cur = cur->next->next;
        }
        return dummyHead->next;
    }
};