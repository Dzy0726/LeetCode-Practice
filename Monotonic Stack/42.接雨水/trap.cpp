// Double pointer
class Solution {
public:
    int trap(vector<int>& height) {
        int sum = 0;
        vector<int> maxLeft(height.size(), 0);
        vector<int> maxRight(height.size(), 0);
        maxLeft[0] = height[0];
        for (int i = 1; i < height.size(); i++) {
            maxLeft[i] = max(maxLeft[i - 1], height[i]);
        }
        maxRight[height.size() - 1] = height[height.size() - 1];
        for (int i = height.size() - 2; i >= 0; i--) {
            maxRight[i] = max(maxRight[i + 1], height[i]);
        }
        for (int i = 1; i < height.size() - 1 ; i++) {
            int current = min(maxLeft[i], maxRight[i]) - height[i];
            if (current > 0) sum += current;
        }
        return sum;
    }
};


// Monotonic Stack
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> st;
        int sum = 0;
        st.push(0);
        for (int i = 1; i < height.size(); i++) {
            if (height[i] < height[st.top()]) {
                st.push(i);
            } else if (height[i] == height[st.top()]) {
                st.pop();
                st.push(i);
            } else {
                while (!st.empty() && height[i] > height[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {
                        int high =
                            min(height[st.top()], height[i]) - height[mid];
                        int wide = i - st.top() - 1;
                        sum += high * wide;
                    }
                }
                st.push(i);
            }
        }
        return sum;
    }
};