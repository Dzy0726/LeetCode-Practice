# 代码随想录算法训练营第七天| 哈希表 Part02

## 今日题目

454.[四数相加 II](https://leetcode.cn/problems/4sum-ii/)

383.[赎金信](https://leetcode.cn/problems/ransom-note/) 

15.[三数之和](https://leetcode.cn/problems/3sum/)

18.[四数之和](https://leetcode.cn/problems/4sum/)

## LeetCode  454.四数相加II 

## 题目

给你四个整数数组 `nums1`、`nums2`、`nums3` 和 `nums4` ，数组长度都是 `n` ，请你计算有多少个元组 `(i, j, k, l)` 能满足：

- `0 <= i, j, k, l < n`
- `nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0`

> **示例 1：**
>
> 1. **输入：**nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2] **输出：**2 **解释：** 两个元组如下： (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0 (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0
>
> **示例 2：**
>
> **输入：**nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0] **输出：**1

## 思路

将四个数组两两组合起来，就降维成两数相加。和昨天做的[两数之和](https://pkdwxagc9o.feishu.cn/wiki/H7EiwPXcZivmk5kYy7ScyKjyn5f#part-D61zdakIqoi4ACxx3RocyvoanJd)思路就相同了。数据结构我选择使用map，因为map可以存一对key-value，key存放两个数组元素之和，value存放这个和出现的次数，用于后续计算有几对i,j,k,l。同时map也可以按key查找，对于后两个数组的组合，直接在map中查找有无对应补数，若有就把对应补数的出现次数加到result中。

## 代码

```C++
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        int n = nums1.size();
        int result = 0;
        unordered_map <int, int> map1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int sum = nums1[i] + nums2[j];
                map1[sum]++;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int comp = - (nums3[i] + nums4[j]);
                result += map1[comp];
            }
        }
        return result;
    }
};
```

## 时空复杂度

时间复杂度：两层循环遍历，时间复杂度为O(n^2).

空间复杂度：O(n^2)，最坏情况下A和B的值各不相同，相加产生的数字个数为 n^2

## 学习与小结

用很短的时间就做出来说明学习还是有成效，思路也和代码随想录的解法一样。

## LeetCode 383.赎金信

## 题目

给你两个字符串：`ransomNote` 和 `magazine` ，判断 `ransomNote` 能不能由 `magazine` 里面的字符构成。

如果可以，返回 `true` ；否则返回 `false` 。

`magazine` 中的每个字符只能在 `ransomNote` 中使用一次。

> **示例 1：**
>
> **输入：**ransomNote = "a", magazine = "b" **输出：**false
>
> **示例 2：**
>
> **输入：**ransomNote = "aa", magazine = "ab" **输出：**false
>
> **示例 3：**
>
> **输入：**ransomNote = "aa", magazine = "aab" **输出：**true

## 思路

用map将`magazine`中的每个字符存起来，key为`magazine`中的各个字符，value为字符在`magazine`中出现的次数。再遍历`ransomNote`，如果`ransomNote`的字符在map中的value小于等于0，就说明该字符在`ransomNote`中不在`magazine`中或是在`magazine`中出现的次数小于在`ransomNote`中出现的次数，返回`false`；如果value大于0，则让map中对应的value减一，继续遍历。如果成功遍历完成`ransomNote`，说明`ransomNote`可以由`magazine`中的字符构成，返回`true`。

## 代码

```C++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map <char, int> map;
        for (auto charac : magazine) {
            map[charac]++;
        }
        for (auto charac : ransomNote) {
            if (map[charac] <= 0) {
                return false;
            }
            map[charac]--;
        }
        return true;
    }
};
```

## 时空复杂度

时间复杂度：遍历了magazine一次，最坏情况遍历ransomNote一次，如果两个字符串的长度分别为m和n，则时间复杂度为O(m+n).

空间复杂度：新建了map存放magazine中的字符及出现次数，所以空间复杂度为O(n).

## 学习与小结

没有注意到两个字符串都只有小写字母组成。并不是说所有的哈希表都直接用map，在本题的情况下，使用map的空间消耗要比数组大一些的，因为map要维护红黑树或者哈希表，而且还要做哈希函数，是费时的！数据量大的话就能体现出来差别了。 所以数组更加简单直接有效！

可以直接用一个长度为26的数组来记录，这样的话空间复杂度就降低到O(1)。

```C++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int record[26] = {0};
        //add
        if (ransomNote.size() > magazine.size()) {
            return false;
        }
        for (int i = 0; i < magazine.length(); i++) {
            // 通过record数据记录 magazine里各个字符出现次数
            record[magazine[i]-'a'] ++;
        }
        for (int j = 0; j < ransomNote.length(); j++) {
            // 遍历ransomNote，在record里对应的字符个数做--操作
            record[ransomNote[j]-'a']--;
            // 如果小于零说明ransomNote里出现的字符，magazine没有
            if(record[ransomNote[j]-'a'] < 0) {
                return false;
            }
        }
        return true;
    }
};
```

还有要注意的是，要看`ransomNote`能否由`magazine`组成，那么当`ransomNote`长度大于`magazine`时，肯定无法满足要求，这样直接返回false，可以提高效率。

## LeetCode 15.三数之和

## 题目

给你一个整数数组 `nums` ，判断是否存在三元组 `[nums[i], nums[j], nums[k]]` 满足 `i != j`、`i != k` 且 `j != k` ，同时还满足 `nums[i] + nums[j] + nums[k] == 0` 。请

你返回所有和为 `0` 且不重复的三元组。

**注意：**答案中不可以包含重复的三元组。

> **示例 1：**
>
> **输入：**nums = [-1,0,1,2,-1,-4] **输出：**[[-1,-1,2],[-1,0,1]] **解释：** nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。 nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。 nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。 不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。 注意，输出的顺序和三元组的顺序并不重要。
>
> **示例 2：**
>
> **输入：**nums = [0,1,1] **输出：**[] **解释：**唯一可能的三元组和不为 0 。
>
> **示例 3：**
>
> **输入：**nums = [0,0,0] **输出：**[[0,0,0]] **解释：**唯一可能的三元组和为 0 。

## 思路

想法是将三数和转化为两数和，先用两层循环将前两数之和存到map中，再遍历一次数组，在map中有没有第三数的相反数。题目要求返回不重复的三元组，去重真的好困难……而且为了存放原始值，map构建是key是两数之和，value是一个pair<int,int>，存放了原来的两个数。最后写出了308/312，在第309超时了。由于multimap的不熟练以及对于三元组去重的不熟练，整体感觉自己的思路乱糟糟的。

## 代码

错误代码(308/312)

```C++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        multimap<int, pair<int, int>> map;
        vector <vector <int>> result;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                map.insert({nums[i]+nums[j], make_pair(i,j)});
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            int comp = -nums[i];
            auto range = map.equal_range(comp);
            if (range.first != range.second) {
                for (auto it = range.first; it != range.second; ++it) {
                    if (it->second.first != i && it->second.second != i) {
                        result.push_back(vector<int>{nums[i],nums[it->second.first],nums[it->second.second]});
                    }
                }
            }
        }
        for (auto &v : result) {
            sort(v.begin(), v.end());
        }
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
        return result;
    }
};
```

## 时空复杂度

时间复杂度：O(n^2).

空间复杂度：O(n).

## 学习与小结

其实这道题目使用哈希法并不十分合适，因为在去重的操作中有很多细节需要注意，在面试中很难直接写出没有bug的代码。而且使用哈希法在使用两层for循环的时候，能做的剪枝操作很有限，虽然时间复杂度是O(n^2)，也是可以在leetcode上通过，但是程序的执行时间依然比较长 。

应该使用**双指针法**。

最后需要返回的是元素的值，与下标无关，所以我们可以先对数组进行排序。

排序后，用i遍历数组，nums[i]就当作a，此时数组是有序的，我们让left先指向i+1，nums[left]作为b，right先指向数组末尾位置，nums[right]作为c。当`a + b + c > 0 `时，说明三个数中最大的数过大了，需要缩小这个数，因为数组有序（升序），所以我们让right左移；当`a + b + c < 0 `时，说明此时需要增大三数之和，又因为我们固定a不动，所以要增加b的值，让left右移。当`a + b + c = 0 `时，我们记录下这三个数字。

双指针法的逻辑还是通俗易懂的，主要难在如何对数据进行去重。

考虑例子`[-1,-1,0,0,1,1]`，当`i=0，left = 2，right=5`时，我们第一次找到了符合题目要求的三个数字，如果不做去重处理，接下来`left`右移一位，`right`左移一位，仍然符合题目要求，但是此时与上个结果重复了。所以我们在每次有新的结果保存后，检查`left`和`right`右移之后的值与当前的值是否相等，如果有相同就跳过继续移动。因为此时a是固定的，b和c只要有一个与之前相同，那么必定abc都与之前相同，就会产生重复的三元组。

完成了b和c的去重，那么a怎么去重呢？还是上面的这个例子，假设此时我们执行完了`i=0`这次循环，也就是已经保存了所有`a=-1`时可能的结果，`i++`后来到`i=1`，发现a仍然是-1，这轮循环是没有意义的，而且会产生相同的重复结果。所以当`nums[i] == nums[i - 1]`时，就要结束当前这轮循环。

为什么不`nums[i] == nums[i + 1]`时结束本轮循环呢？考虑例子`[-1,-1,2]`，如果在`nums[i] == nums[i + 1]`时结束本轮循环，就错过了一个正确答案。题目要求最后的三元组不能有重复，但没有说每个三元组内的元素不能有重复。所以要在记录下a的所有情况后再次碰到a跳过，而不能还没有记录就跳过循环。

```C++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector <vector<int>> result;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) {
                return result;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum > 0) {
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    left++;
                    right--;
                }
            }
        }
        return result;
    }
};
```

在b和c去重时，注意代码的顺序，需要先判断`left < right`，再比较两组值，否则会发生越界问题。

考虑例子`[0,0,0,0]`，当`i=0，left=1，right=3`时找到了一组正确答案，如果先判断`nums[left] == nums[left + 1]`，left=1时没有问题left++；left=2时没有问题left++；当left=3时会访问到nums[4]，产生数组越界问题，所以需要先判断此时left是否在界内，即与初始指向数组末尾元素的right来比较。

## LeetCode 18.四数之和

## 题目

给你一个由 `n` 个整数组成的数组 `nums` ，和一个目标值 `target` 。请你找出并返回满足下述全部条件且**不重复**的四元组 `[nums[a], nums[b], nums[c], nums[d]]` （若两个四元组元素一一对应，则认为两个四元组重复）：

- `0 <= a, b, c, d < n`
- `a`、`b`、`c` 和 `d` **互不相同**
- `nums[a] + nums[b] + nums[c] + nums[d] == target`

你可以按 **任意顺序** 返回答案 。

> **示例 1：**
>
> **输入：**nums = [1,0,-1,0,-2,2], target = 0 **输出：**[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
>
> **示例 2：**
>
> **输入：**nums = [2,2,2,2,2], target = 8 **输出：**[[2,2,2,2]]

## 思路

在三数之和的基础上，很快地写出了这道题的主体代码，可是在细节上调试了一个小时最后还是没有靠自己AC。

1. 首先是在三数之和中，我们可以有一层剪枝：`nums[i] > 0`，但在四数之和中，`target`是任意值，这就说明`target`可以是负数，所以如果加上这个剪枝就会出现跳过正确答案的情况。比如：`[-5,-4,-3,-2,1,3,3,5]`，target是-11，如果继续这样剪枝就会导致`nums[0] > target`而结束，导致错误。
2. 然后是对重复值的处理，把自己陷入了死循环。三数之和对a去重时，如果`num[i] == nums[i - 1]`，就说明重复，可以跳过这次循环；在四数之和陷入了：必须把a和b当作整体，当作是三数之和的a，然后对a+b整体去重，这就导致当测试用例是：`[-3,-2,-1,0,0,1,2,3]`时，单纯的靠a+b的和会过度去重，但具体靠a和b的值，又会极大的增加处理的难度。所以最后利用vector的`unique`和`erase`去重。
3. 由于去重逻辑不正确，就导致遇到了`longlong` 类型的问题。当数据和超出int范围，自己又不会处理，问过GPT才得到了处理方式，最后勉强AC。

## 代码

```C++
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
        std::vector<std::vector<int>> result;
        std::sort(nums.begin(), nums.end());
        
        long long target_ll = static_cast<long long>(target); // 将 target 转换为 long long 类型
        
        for (size_t i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue; // 避免重复的 i
            }
            
            for (size_t j = i + 1; j < nums.size(); j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue; // 避免重复的 j
                }
                
                size_t left = j + 1;
                size_t right = nums.size() - 1;
                while (left < right) {
                    long long sum = static_cast<long long>(nums[i]) + nums[j] + nums[left] + nums[right];
                    if (sum > target_ll) {
                        right--;
                    } else if (sum < target_ll) {
                        left++;
                    } else {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) {
                            left++;
                        }
                        while (left < right && nums[right] == nums[right - 1]) {
                            right--;
                        }
                        left++;
                        right--;
                    }
                }
            }
        }
        
        return result;
    }
};
```

## 时空复杂度

时间复杂度：O(n^3).

空间复杂度：O(1).

## 学习与小结

对于双指针的逻辑以及双指针的去重掌握较好，但是对于固定值a、b的去重没有理清思路。

1. 首先是对于`Long Long`类型的解决：之所以会遇到这个问题，是因为在开头没有处理好。因为在调试过程中遇到了`[-5,-4,-3,-2,1,3,3,5]`，target是-11，如果继续这样剪枝就会导致`nums[0] > target`而结束的问题，所以删除了剪枝。其实不管是整数还是负数，这层剪枝是可以保留的，可以对target加一个正负判断，如果target是非负，就和三数之和的处理一样，如果target是负数，那么不做处理。

   1. ```C++
      if (target >=0 && nums[i] > target) break;
      if (target >=0 && nums[j] + nums[i] > target) break;
      ```

   2.  LongLong转换方式：

   3. ```C++
        long long target_ll = static_cast<long long>(target); // 将 target 转换为 long long 类型
      ```

2. 对于重复值的处理：没必要想的过于复杂，要在二层剪枝时对两个值一起处理，其实单独处理就可以。对于a去重，和三数之和的处理方式一样，当固定a结束一次循环后，发现i++后的a还是之前的a，说明这轮没有必要再进行了，直接跳过即可；对于b去重，在a固定不动，发现b和之前的值相同，就跳过这轮，**但是要注意j的范围！**

   1.  j的起始值是i+1，所以必须要当`j > i + 1`，在处理，`j = i + 1`说明刚进入循环，完全存在`nums[i]`和`nums[j]`相同的情况。

   2. 想的太多容易把自己陷进去，理清逻辑一步步来即可。

   3. ```C++
          for (size_t i = 0; i < nums.size(); i++) {
                  if (i > 0 && nums[i] == nums[i - 1]) {
                      continue; // 避免重复的 i
                  }
                  
                  for (size_t j = i + 1; j < nums.size(); j++) {
                      if (j > i + 1 && nums[j] == nums[j - 1]) {
                          continue; // 避免重复的 j
                      }
                   }
           }
      ```

最终版本代码：

```C++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (target >= 0 && nums[i] > target) {
                break;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            long long target_ll = static_cast<long long>(target);
            for (int j = i + 1; j < nums.size(); j++) {
                if (target >= 0 && nums[i] + nums[j] > target) {
                    break;
                }
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                int left = j + 1;
                int right = nums.size() - 1;
                while (left < right) {
                    long long sum = static_cast<long long>(nums[i]) + nums[j] +
                                    nums[left] + nums[right];
                    if (sum > target_ll) {
                        right--;
                    } else if (sum < target_ll) {
                        left++;
                    } else {
                        result.push_back(vector<int>{nums[i], nums[j],
                                                     nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) {
                            left++;
                        }
                        while (left < right && nums[right] == nums[right - 1]) {
                            right--;
                        }
                        left++;
                        right--;
                    }
                }
            }
        }
        return result;
    }
};
```