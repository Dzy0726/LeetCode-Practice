/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-01 21:28:09
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-01 21:30:12
 * @FilePath: \LeetCode-Practice\LinkList\82.删除排序链表中的重复元素II\deleteDuplicates.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
// Solution 1: My Solution
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode * dummyHead = new ListNode();
        dummyHead -> next = head;
        ListNode * current = dummyHead;
        bool isDelete = false;
        while (current -> next && current -> next -> next) {
            ListNode * pre = current -> next;
            ListNode * post = current -> next -> next;
            if (pre -> val == post -> val) {
                current -> next = post;
                isDelete = true;
            } else {
                if (isDelete == true) {
                    current -> next = post;
                    isDelete = false;
                } else {
                    current = current -> next;
                }
            }
        }
        if (isDelete == true) {
            current -> next = current -> next -> next;
        }
        return dummyHead -> next;
    }
};


// Solution 2: LeetCode Solution
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) {
            return head;
        }
        
        ListNode* dummy = new ListNode(0, head);

        ListNode* cur = dummy;
        while (cur->next && cur->next->next) {
            if (cur->next->val == cur->next->next->val) {
                int x = cur->next->val;
                while (cur->next && cur->next->val == x) {
                    cur->next = cur->next->next;
                }
            }
            else {
                cur = cur->next;
            }
        }

        return dummy->next;
    }
};