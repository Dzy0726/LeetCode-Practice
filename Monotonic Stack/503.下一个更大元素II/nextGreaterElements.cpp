// Solution1
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st;
        vector<int> result(nums.size() * 2, -1);
        vector<int> nums2(nums.size() * 2);
        copy(nums.begin(), nums.end(), nums2.begin());
        copy(nums.begin(), nums.end(), nums2.begin() + nums.size());
        // nums.insert(nums.end(), nums.begin(), nums.end());
        st.push(0);
        for (int i = 1; i < nums.size() * 2; i++) {
            while (!st.empty() && nums2[i] > nums2[st.top()]) {
                result[st.top()] = nums2[i];
                st.pop();
            }
            st.push(i);
        }
        result.resize(nums.size());
        return result;
    }
};

// Solution2
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st;
        vector<int> result(nums.size(), -1);
        st.push(0);
        for (int i = 1; i < nums.size() * 2; i++) {
            while (!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
                result[st.top()] = nums[i % nums.size()];
                st.pop();
            }
            st.push(i % nums.size());
        }
        return result;
    }
};