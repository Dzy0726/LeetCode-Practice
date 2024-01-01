/*** 
 * @Author: Dzy0726
 * @Date: 2024-01-02 00:01:32
 * @LastEditors: Dzy0726
 * @LastEditTime: 2024-01-02 00:01:44
 * @FilePath: \LeetCode-Practice\LinkList\328.奇偶链表\oddEvenList.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode * dummyEven = new ListNode();
        ListNode * curEven = dummyEven;
        ListNode * curOdd = head;
        while (curOdd -> next) {
           curEven -> next = curOdd -> next;
           curEven = curEven -> next;
           if (curEven -> next != nullptr) {
                curOdd -> next = curEven -> next;
                curOdd = curOdd -> next;
           } else {
               break;
           }
          
        }
        curEven -> next = nullptr;
        curOdd -> next = dummyEven -> next;
        return head;
    }
};