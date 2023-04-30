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