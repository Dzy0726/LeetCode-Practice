// My Bad Solution 46/51
class Solution {
public:
    int findMax(queue<int> q) {
        int max = -INT32_MAX;
        while (!q.empty()) {
            max = q.front() > max ? q.front() : max;
            q.pop(); 
        }
        return max;
    }

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector <int> result;
        queue <int> q;
        int max = -INT32_MAX;
        int i = 0;
        for (; i < k; i++) {
            max = nums[i] > max ? nums[i] : max;
            q.push(nums[i]);
        }
        result.push_back(max);
        for (; i < nums.size(); i++) {
            if (nums[i] >= max) {
                max = nums[i];
                q.pop();
                q.push(nums[i]);
                result.push_back(max);
            } else {
                if (q.front() != max) {
                    q.pop();
                    q.push(nums[i]);
                    result.push_back(max);
                } else {
                    q.pop();
                    q.push(nums[i]);
                    max = findMax(q);
                    result.push_back(max);
                }
            }
        }
        return result;     
    }
};

// A Better Solution
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        Myqueue que;
        vector<int> result;
        int i = 0;
        for (; i < k; i++) {
            que.push(nums[i]);
        }
        result.push_back(que.front());
        for (; i < nums.size(); i++) {
            que.pop(nums[i - k]);
            que.push(nums[i]);
            result.push_back(que.front());
        }
        return result;
    }

private:
    class Myqueue {
    public:
        deque<int> q;
        void pop(int val) {
            if (!q.empty() && q.front() == val) {
                q.pop_front();
            }
        }

        void push(int val) {
            while (!q.empty() && q.back() < val) {
                q.pop_back();
            }
            q.push_back(val);
        }

        int front() {
            return q.front();
        }
    };
};


// Fantastic!
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int> st;
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (i >= k) st.erase(st.find(nums[i - k]));
            st.insert(nums[i]);
            if (i >= k - 1) ans.push_back(*st.rbegin());
        }
        return ans;
    }
};