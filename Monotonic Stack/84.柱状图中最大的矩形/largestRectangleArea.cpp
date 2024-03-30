class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int result = 0;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        stack<int> st;
        st.push(0);
        for (int i = 1; i < heights.size(); i++) {
            if (heights[i] > heights[st.top()]) {
                st.push(i);
            } else if (heights[i] == heights[st.top()]) {
                st.pop();
                st.push(i);
            } else {
                while (!st.empty() && heights[i] < heights[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    int high = heights[mid];
                    int wide = i - st.top() - 1;
                    result = max(result, wide * high);
                }
                st.push(i);
            }
        }
        return result;
    }
};