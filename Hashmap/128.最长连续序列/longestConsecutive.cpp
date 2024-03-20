/*
    这不是O(n)算法，排序起码是O(nlogn)
    做的时候忽略了如果排序完后连续几个相同，比如{0,1,1,2,3}
    应该加上比较条件，如果相邻两个相同就跳过这次循环
*/
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int result = 1;
        int count = 1;
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                continue;
            }
            if (nums[i] - nums[i - 1] == 1) {
                count++;
            } else {
                count = 1;
            }
            result = max(result, count);
        }
        return result;
    }
};

/*NOTE - 
    可以用哈希集合（std::unordered_set）降低时间复杂度到O(n)
    遍历数组，如果当前数组是一个连续序列的开始，就从他开始计算连续的长度
    如何计算是连续序列的开始？set中不存在num - 1
    如何计算连续序列的长度？while循环找current+1，并且每次找到都更新currentLength
    for循环嵌套while循环？时间复杂度依旧是O(n)，手动模拟可以发现每个元素只查了一次
*/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> set;
        for (int num : nums) {
            set.insert(num);
        }
        int result = 0;
        for (int num : nums) {
            if (!set.count(num - 1)) {
                int current = num;
                int count = 1;
                while (set.count(current + 1)) {
                    current += 1;
                    count += 1;
                }
                result = max(result, count);
            }
        }
        return result;
    }
};