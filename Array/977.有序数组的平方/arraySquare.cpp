class Solution {
public:

    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> result(nums.size(),0);
        int k = nums.size() - 1;
        int i = 0, j = k;
        while(i <= j) {
            if(nums[i] * nums[i] < nums[j] *nums[j]) {
                result[k--] = nums[j] * nums[j];
                j--;
            } else {
                result[k--] = nums[i] * nums[i];
                i++;
            }
        }
        return result;
    }
};


//暴力：
class Solution {
public:

    vector<int> sortedSquares(vector<int>& nums) {
        for(int i = 0; i < nums.size(); i++) {
            nums[i] = nums[i] * nums[i];
        }
        sort(nums.begin(),nums.end());
        return nums;
    }
};