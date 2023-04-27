/*** 
 * @Author: Zhenyu Dong
 * @Date: 2023-04-27 16:32:28
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2023-04-27 16:33:22
 * @FilePath: /19.删除链表的倒数第N个节点/deleteNnode.cpp
 * @Description: 
 * @
 * @Copyright (c) 2023 by Zhenyu Dong, All Rights Reserved. 
 */
class Solution {
public:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode * dummyHead = new ListNode();
        dummyHead->next = head;
        ListNode * cur = new ListNode();
        cur = head;
        int length = 0,count;
        while(cur) {
            length++;
            cur = cur->next;
        }
        count = length - n;
        if(count == 0) {
            dummyHead->next = head->next;
            return dummyHead->next;
        } else {
            cur = head;
            while(--count > 0) {
                cur = cur->next;
            }
            ListNode * del = new ListNode();
            del = cur->next;
            cur->next = cur->next->next;
            delete del;  
        }
        
        return dummyHead->next;
    }
};