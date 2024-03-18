class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        vector<int> resIdx(nums2.size(), 0);
        vector<int> result(nums1.size(), -1);
        st.push(0);
        for (int i = 1; i < nums2.size(); i++) {
            while (!st.empty() && nums2[i] > nums2[st.top()]) {
                resIdx[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        for (int i = 0; i < nums1.size(); i++) {
            int index = -1;
            // 这段用哈希表优化性能
            for (int j = 0; j < nums2.size(); j++) {
                if (nums1[i] == nums2[j]) {
                    index = j;
                    break;
                }
            }
            if (resIdx[index] != 0) {
                result[i] = nums2[resIdx[index]];
            }
        }
        return result;
    }
};