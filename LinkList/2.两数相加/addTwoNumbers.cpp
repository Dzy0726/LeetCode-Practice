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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        ListNode* result;
        int len1 = 0, len2 = 0;
        while (cur1) {
            len1++;
            cur1 = cur1->next;
        }
        while (cur2) {
            len2++;
            cur2 = cur2->next;
        }
        if (len1 > len2) {
            result = l1;
        } else {
            result = l2;
        }
        ListNode* resCur = result;
        cur1 = l1;
        cur2 = l2;
        int plusOne = 0;
        while (resCur) {
            int currentSum = 0;
            if (cur1 == NULL) {
                currentSum = cur2 -> val + plusOne;
            } else if (cur2 == NULL) {
                currentSum = cur1 -> val + plusOne;
            } else {
                currentSum = cur1 -> val + cur2 -> val + plusOne;
            }
            resCur -> val = currentSum % 10;
            cout << resCur ->val << endl;
            if (currentSum >= 10) {
                plusOne = 1;
            } else {
                plusOne = 0;
            }
            if (cur1 != NULL) {
                cur1 = cur1 -> next;
            } 
            if (cur2 != NULL) {
                cur2 = cur2 -> next;
            }
            if (resCur -> next == NULL && plusOne == 1) {
                ListNode* append = new ListNode(1);
                resCur -> next = append;
                break;
            }
            resCur = resCur -> next;
        }
        return result;
    }
};