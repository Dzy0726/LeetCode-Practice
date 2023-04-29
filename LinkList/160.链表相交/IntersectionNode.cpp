/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:

    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *curA = headA;
        ListNode *curB = headB;
        int lenA = 0;
        int lenB = 0;
        while(curA != NULL) {
            lenA++;
            curA = curA->next;
        }
        while(curB != NULL) {
            lenB++;
            curB = curB->next;
        }
        curA = headA;
        curB = headB;
        int n = lenA > lenB ? (lenA - lenB) : (lenB - lenA);
        // 让curA为最长链表的头，lenA为其长度
        if (lenB > lenA) {
            swap (lenA, lenB);
            swap (curA, curB);
        }
        while(n--) {
            curA = curA->next;
        }
        while(curA) {
            if(curA == curB) {
                break;
            } else {
                curA = curA->next;
                curB = curB->next;
            }
        }
        return curA;
    }
};