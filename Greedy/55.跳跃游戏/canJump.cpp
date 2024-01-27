class Solution {
public:
    bool canJump(vector<int>& nums) {
        int cover = nums[0];
        for (int i = 0; i <= cover; i++) {
            if (cover >= nums.size() - 1) return true;
            int newCover = i + nums[i];
            cover = cover > newCover ? cover : newCover;
        }
        return false;
    }
};