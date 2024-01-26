// My Solution
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() == 1) return 1;
        int result = 1;
        int big; 
        if (nums[1] > nums[0]) {
            big = 1;
            result++;
        } else if (nums[1] < nums[0]) {
            big = 0;
            result++;
        } else {
            big = 2;
        }
        for (int i = 2; i < nums.size(); i++) {
            if (big == 1) {
                if (nums[i] < nums[i - 1]) {
                    result++;
                    big = 0;
                }
            } else if (big == 0){
                if (nums[i] > nums[i - 1]) {
                    result++;
                    big = 1;
                }
            } else {
                if (nums[i] > nums[i - 1]) {
                    result++;
                    big = 1;
                } else if (nums[i] < nums[i - 1]) {
                    result++;
                    big = 0;
                } else {
                    continue;
                }
            }
        }
        return result;
    }
};


// A Better Solution
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        int curDiff = 0; // 当前一对差值
        int preDiff = 0; // 前一对差值
        int result = 1;  // 记录峰值个数，序列默认序列最右边有一个峰值
        for (int i = 0; i < nums.size() - 1; i++) {
            curDiff = nums[i + 1] - nums[i];
            // 出现峰值
            if ((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) {
                result++;
                preDiff = curDiff; // 注意这里，只在摆动变化的时候更新prediff
            }
        }
        return result;
    }
};