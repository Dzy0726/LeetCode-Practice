class Solution {
public:
    struct ListNode {
        int val;
        ListNode *next;
    };
 
    ListNode *detectCycle(ListNode *head) {
        vector<ListNode*> myls;
        ListNode * cur = head;
        bool isExist = false;
        while(cur != NULL) {
            for(int i = 0; i < myls.size(); i++) {
                if(myls[i] == cur) {
                    isExist = true;
                    break;
                }
            }
            if(isExist) break;
            
            myls.push_back(cur);
            cur = cur->next;
        }
        return cur;
    }
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                ListNode *index1 = head;
                ListNode *index2 = fast;
                while(index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index1;
            }
        }
        return NULL;
    }
};