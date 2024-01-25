class Solution {
public:
    unordered_map<string, map<string, int>> map_tickets;
    vector<string> result;
    bool backtracking(int ticketNum) {
        if (result.size() == ticketNum + 1) {
            return true;
        }
        for (pair<const string, int>& t : map_tickets[result.back()]) {
            if (t.second > 0) {
                t.second--;
                result.push_back(t.first);
                if (backtracking(ticketNum)) return true;
                t.second++;
                result.pop_back();
            }
        }
        return false;
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        int ticketNum = tickets.size();
        for (vector<string> vec : tickets) {
            map_tickets[vec[0]][vec[1]]++;
        }
        result.push_back("JFK");
        backtracking(ticketNum);
        return result;
    }
};