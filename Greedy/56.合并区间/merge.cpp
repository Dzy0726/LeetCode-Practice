class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> result;
        vector<int> overlap = intervals[0];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= overlap[1]) {
                overlap[0] = min(overlap[0], intervals[i][0]);
                overlap[1] = max(overlap[1], intervals[i][1]);
            } else {
                result.push_back(overlap);
                overlap = intervals[i];
            }
        }
        result.push_back(overlap);
        return result;
    }
};