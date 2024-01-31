class Solution {
public:
    static bool cmp (const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] < b[0];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        int count = 0;
        vector<int> overlap = intervals[0];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= overlap[1]) {
                overlap = intervals[i];
                continue;
            }
            overlap[0] = max(overlap[0], intervals[i][0]);
            overlap[1] = min(overlap[1], intervals[i][1]);
            count++;
        }
        return count;
    }
};