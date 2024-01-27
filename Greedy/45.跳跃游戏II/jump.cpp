// My Solution
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int cover = nums[0];
        int count = 1;
        int newCover = cover;
        int newStart = 0;
        for (int i = 0; i <= cover; i++) {
            if (cover >= nums.size() - 1) {
                break;
            }
            if (nums[i] + i > newCover) {
                newCover = nums[i] + i;
                newStart = i;
            }
            if (i == cover) {
                cover = newCover;
                count++;
                i = newStart;
            }
        }
        return count;
    }
};

// A Better Solution
class Solution {
public:
    int jump(vector<int>& nums) {
        int current_end = 0; // 当前跳跃能到达的最远边界
        int next_end = 0; // 下一跳可以到达的最远位置
        int steps = 0; // 跳跃次数
        // 遍历数组元素，但不需要访问最后一个元素，因为在到达最后一个元素之前我们就已经跳跃了
        for (int i = 0; i < nums.size() - 1; ++i) {
            next_end = max(next_end, i + nums[i]); // 更新下一跳可达的最远位置
            // 当我们到达当前跳跃的边界时，我们进行跳跃，并更新当前的边界
            if (i == current_end) {
                current_end = next_end;
                ++steps;
                // 如果当前边界已经可以到达数组的最后一个位置，则结束循环
                if (current_end >= nums.size() - 1) break;
            }
        }
        return steps;
    }
};