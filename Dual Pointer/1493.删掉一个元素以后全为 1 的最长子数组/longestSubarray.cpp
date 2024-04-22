// 允许删掉一个0，就是窗口内0的数量最多是1，大于1了就得滑动窗口，直到0的数量小于等于1，从这里入手思考会比较顺畅
// 说到底还是一个模板题，模板不熟练，使用太死板
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int left = 0;
        int result = 0;
        int count = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) {
                count++;
            }
            while (count > 1) {
                if (nums[left] == 0) {
                    count--;
                }
                left++;
            }
            result = max(result, right - left + 1);
        }
        return result - 1;
    }
};