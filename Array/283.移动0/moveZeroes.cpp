class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i = 0, j = 0;
        while (i < nums.size()) {
            if (nums[i] != 0) {
                nums[j++] = nums[i++];
            } else {
                i++;
            }
        }
        while (j < nums.size()) {
            nums[j++] = 0;
        }
    }
};