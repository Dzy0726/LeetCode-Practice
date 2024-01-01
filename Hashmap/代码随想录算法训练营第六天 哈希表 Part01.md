# 代码随想录算法训练营第六天| 哈希表 Part01

## 今日题目

242.[有效的字母异位词](https://leetcode.cn/problems/valid-anagram/)

349.[两个数组的交集](https://leetcode.cn/problems/intersection-of-two-arrays/)

202.[快乐数](https://leetcode.cn/problems/happy-number/)

1.[两数之和](https://leetcode.cn/problems/two-sum/)

哈希表可以快速判断一个元素是否出现集合里

哈希法牺牲了空间换取了时间

## 哈希表理论基础

### 哈希碰撞（冲突）

两个或多个元素的索引位置相同，即key相同，发生冲突。

解决方法：拉链法和线性探测法。

### C++哈希表

在C++中，set 和 map 分别提供以下三种数据结构，其底层实现以及优劣如下表所示：

| 集合               | 底层实现 | 是否有序 | 数值是否可以重复 | 能否更改数值 | 查询效率 | 增删效率 |
| ------------------ | -------- | -------- | ---------------- | ------------ | -------- | -------- |
| std::set           | 红黑树   | 有序     | 否               | 否           | O(log n) | O(log n) |
| std::multiset      | 红黑树   | 有序     | 是               | 否           | O(logn)  | O(logn)  |
| std::unordered_set | 哈希表   | 无序     | 否               | 否           | O(1)     | O(1)     |

std::unordered_set底层实现为哈希表，std::set 和std::multiset 的底层实现是红黑树，红黑树是一种平衡二叉搜索树，所以key值是有序的，但key不可以修改，改动key值会导致整棵树的错乱，所以只能删除和增加。

| 映射               | 底层实现 | 是否有序 | 数值是否可以重复 | 能否更改数值 | 查询效率 | 增删效率 |
| ------------------ | -------- | -------- | ---------------- | ------------ | -------- | -------- |
| std::map           | 红黑树   | key有序  | key不可重复      | key不可修改  | O(logn)  | O(logn)  |
| std::multimap      | 红黑树   | key有序  | key可重复        | key不可修改  | O(log n) | O(log n) |
| std::unordered_map | 哈希表   | key无序  | key不可重复      | key不可修改  | O(1)     | O(1)     |

std::unordered_map 底层实现为哈希表，std::map 和std::multimap 的底层实现是红黑树。同理，std::map 和std::multimap 的key也是有序的（这个问题也经常作为面试题，考察对语言容器底层的理解）。

当我们要使用集合来解决哈希问题的时候，优先使用unordered_set，因为它的查询和增删效率是最优的，如果需要集合是有序的，那么就用set，如果要求不仅有序还要有重复数据的话，那么就用multiset。

那么再来看一下map ，在map 是一个key value 的数据结构，map中，对key是有限制，对value没有限制的，因为key的存储方式使用红黑树实现的。

### C++代码实现

#### 声明

```C++
 unordered_map<const Key, T> map;
 /* 迭代器 */
 unordered_map<Key,T>::iterator it;
(*it).first;             // the key value (of type Key)
(*it).second;            // the mapped value (of type T)
(*it);                   // the "element value" (of type pair<const Key,T>) 
```

**it->first返回的是key值，it->second返回的是value值**

#### **构造函数**

```C++
unordered_map<int,int>hashmap_1;//构造空的容器
unordered_map<string,int>hashmap_2{{"Jan",44}, {"Jim", 33}, {"Joe", 99}};//直接构造
unordered_map<string,int>hashmap_3(hashmap_2);// 复制初始化
unordered_map<string,int>hashmap_4(hashmap_2.begin(),hashmap_2.end());// 范围初始化
```

#### 容量操作

- size：返回unordered_map容器中的元素数量
- max_size：返回unordered_map容器可以容纳的元素的最大数量
- bucket count：容器内部bucket的数量
- empty：如果容器大小为0则返回true，否则返回false
- load_factor：负载因子

#### 元素操作

- 查找元素：查找key所在的元素。找到：返回元素的迭代器，通过迭代器的first和second属性获取值；没找到：返回unordered_map::end

- 插入元素：

  - ```C++
    myrecipe.insert (myshopping);                        // 复制插入
    myrecipe.insert (make_pair<string,double>("eggs",6.0)); // 移动插入
    myrecipe.insert (mypantry.begin(), mypantry.end());  // 范围插入
    myrecipe.insert ({{"sugar",0.8},{"salt",0.1}});    // 初始化数组插入(可以用二维一次插入多个元素，也可以用一维插入一个元素)
    myrecipe["coffee"] = 10.0;  //数组形式插
    ```

- at：查找key所对应的值。如果存在：返回key对应的值，可以直接修改，和[]操作一样。如果不存在：抛出 out_of_range异常

- erase：删除元素

  - ```C++
     mymap.erase(mymap.begin());//删除单个元素
     mymap.erase(1112);//通过key值删除元素
     mymap.erase(mymap.find(1114), mymap.end());//范围删除元素
    ```

- clear：清空元素，清空元素后，size()变为0，但maxsize保持不变

- swap：交换两个unordered_map（注意，不是交换特定元素，是整个交换两个map中的所有元素）

## LeetCode 242.有效的字母异位词 

### 题目

给定两个字符串 *`s`* 和 *`t`* ，编写一个函数来判断 *`t`* 是否是 *`s`* 的字母异位词。

**注意：**若 *`s`* 和 *`t`* 中每个字符出现的次数都相同，则称 *`s`* 和 *`t`* 互为字母异位词。

> **示例 1:**
>
> **输入:** *s* = "anagram", *t* = "nagaram" **输出:** true
>
> **示例 2:**
>
> **输入:** *s* = "rat", *t* = "car" **输出:** false

### 思路

这道题的思路很容易想到，在看完哈希表的理论基础后，对哈希表应该有一个简单的认知，它由键值对组成，用于查找一个元素是否出现在集合中。所以我们可以先用哈希表记录下第一个字符串出现的字符以及出现的次数，再遍历第二个字符串，将这些次数减去。最后遍历哈希表，如果所有的value都为0，就返回true；只要有一个不为0，就返回false。

### 代码

```C++
class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> count;
        for (int i = 0; i < s.length(); i++) {
            count[s[i]]++;
        }
        for (int i = 0; i < t.length(); i++) {
            count[t[i]]--;
        }
        for (auto it = count.begin(); it != count.end(); ++it) {
            if (it->second != 0) {
                return false;
            }
        }
        return true;
    }
};
```

### 时空复杂度

时间复杂度：遍历两个字符串各一次，遍历哈希表一次，时间复杂度为O(n).

空间复杂度：最坏情况哈希表的长度是26（26个字母），是常量级别的长度，所以空间复杂度为O(1).

### 学习与小结

1. 第一个循环中，我们不需要检查`count.find(s[i])`是否存在，因为`unordered_map`的`operator[]`将在键不存在时插入一个默认初始化的值（对于整数类型，这是`0`）。如果`s[i]`不在映射中，会插入值，然后立即加上1；如果`t[i]`不在映射中，`operator[]`会插入值`0`，然后立即减去`1`。
2. 对于迭代器和其他模板对象来说，通常推荐使用前置递增`++it`，因为它避免了不必要的副本创建，可能更高效。尽管在许多情况下，现代编译器能够优化后置递增以避免额外的开销，但前置递增依然是一个好习惯，特别是在迭代器和复杂对象的上下文中。
3.  `count.end()`不是指向一个"空值"，而是返回一个迭代器，它指向`unordered_map`容器`count`的末尾位置，这个位置是在最后一个元素之后的位置。这个末尾迭代器不指向任何实际的元素，它主要用作一个标记，表示容器的边界，以便我们知道何时停止遍历容器。在C++标准库的容器中，`end()`返回的迭代器通常被称为"past-the-end"迭代器。对它进行解引用是未定义行为，因为它并不表示任何有效的元素。它的主要用途是提供一个循环终止条件。
4. `begin()`方法返回的迭代器是一个指向容器中第一个元素的迭代器。所以与`end()`方法返回的"past-the-end"迭代器不同，`begin()`返回的迭代器确实指向一个实际的元素（前提是容器不为空）。

## LeetCode 349. 两个数组的交集

### 题目

给定两个数组 `nums1` 和 `nums2` ，返回 *它们的交集* 。输出结果中的每个元素一定是 **唯一** 的。我们可以 **不考虑输出结果的顺序** 。

> **示例 1：**
>
> **输入：**nums1 = [1,2,2,1], nums2 = [2,2] **输出：**[2]
>
> **示例 2：**
>
> **输入：**nums1 = [4,9,5], nums2 = [9,4,9,8,4] **输出：**[9,4] **解释：**[4,9] 也是可通过的

### 思路

这道题思路也很简单，因为给定了数据范围

- `1 <= nums1.length, nums2.length <= 1000`
- `0 <= nums1[i], nums2[i] <= 1000`

所以可以新建一个`a[1000]`，初始值赋为-1，遍历nums1数组，将nums1数组中出现的元素在数组a中标记为0；再遍历nums2数组，只要在数组二中出现，就让数组a中对应的元素值加一。最后遍历数组a，只要元素值大于0，就pushback到结果数组中。

另一种方法是使用unordered_map，先遍历nums1，将nums1中出现的数字加入map，并且将value赋值为1；再遍历nums2，并检查map，如果map中nums2的元素对应的值是1，就加入到result，并且将map对应的值更改，如果不更改结果会出现重复。

### 代码

方法一：

```C++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        int a[1000];
        vector <int> result;
        for (int i = 0; i < 1000; i++) {
            a[i] = -1;
        }
        for (int i = 0; i < nums1.size(); i++) {
            if (a[nums1[i]] == -1) {
                a[nums1[i]] = 0;
            }
        }
        for (int i = 0; i < nums2.size(); i++) {
            if (a[nums2[i]] == 0) {
                a[nums2[i]]++;
            }
        }
        for (int i = 0; i < 1000; i++) {
            if (a[i] > 0) {
                result.push_back(i);
            }
        }
        return result;
    }
};
```

方法二

```C++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_map <int, int> map;
        vector <int> result;
        for (int i = 0; i < nums1.size(); i++) {
            map[nums1[i]] = 1;
        }
        for (int i = 0; i < nums2.size(); i++) {
            if (map[nums2[i]] == 1) {
                result.push_back(nums2[i]);
                map[nums2[i]]++;
            }
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：

方法一：初始化数组`a`。这里有一个固定大小的1000的整数数组，初始化这个数组的时间复杂度是`O(1000)`，即`O(1)`，因为它是一个常数时间的操作；遍历`nums1`数组。这个循环的时间复杂度是`O(n)`，其中`n`是`nums1`的长度；遍历`nums2`数组。这个循环的时间复杂度也是`O(m)`，其中`m`是`nums2`的长度。遍历数组`a`来构建`result`向量。这个循环的时间复杂度是`O(1000)`，即`O(1)`。综上所述，时间复杂度为O(m+n+1)，即O(n+m)

方法二：

**遍历****`nums1`****数组**循环中，每个`nums1`中的元素都被插入到`map`中，操作的平均时间复杂度为`O(1)`。因此，这个循环的总时间复杂度是`O(n)`，其中`n`是`nums1`的长度。**遍历****`nums2`****数组**循环的每次迭代操作的平均时间复杂度也为`O(1)`。总的时间复杂度是`O(m)`，其中`m`是`nums2`的长度。**构建****`result`****向量。** 这个操作的时间复杂度取决于`nums2`中与`nums1`相交的元素数量，最坏情况下为`O(min(n, m))`；综上所述，总的平均时间复杂度是`O(n + m)`.

空间复杂度：

方法一：

有一个固定大小的1000的整数数组`a`，这是`O(1)`空间复杂度，因为它与输入大小无关；`result`向量的大小最坏情况下等于`nums1`和`nums2`中较小的数组长度，但它不会超过数组`a`的大小，因此空间复杂度也是`O(1)`。

方法二：

空间复杂度是`O(n + m)`.

### 学习与小结

使用数组来做哈希的题目，是因为题目都限制了数值的大小。如果这道题目没有限制数值的大小，就无法使用数组来做哈希表了。而且如果哈希值比较少、特别分散、跨度非常大，使用数组就造成空间的极大浪费。

如果这道题没有限制数值的大小，我们可以用`unordered_set`来做。为什么使用set？是因为题目要求返回结果不重复，且只需要统计相同的元素，不涉及元素个数。set中的元素不可以重复，是很好的选择。根据[set表格](https://pkdwxagc9o.feishu.cn/docx/UoCSdbpNToOltPxevSUcaXEgn1M#Cvqrdn6p6o4NDxx88Xzcx0mpnjx)，std::set和std::multiset底层实现都是红黑树，std::unordered_set的底层实现是哈希表， 使用unordered_set 读写效率是最高的，并不需要对数据进行排序，而且还不要让数据重复，所以选择unordered_set。

思路如图所示：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ODNlMDQzOWRhMGQ5YTE4YmM5NTRhMjNjNmQ4ZmM1NDJfRTVwREJQVFY0MEVQcUxzN25FME42R3hJNEcyOGlvM2NfVG9rZW46RmJkc2IwTnJwb1ZYREd4R0IwSWNhWVJXbkdlXzE3MDQxMDk2NTI6MTcwNDExMzI1Ml9WNA)

```C++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> result_set; // 存放结果，之所以用set是为了给结果集去重
        unordered_set<int> nums_set(nums1.begin(), nums1.end()); //范围赋值
        for (int num : nums2) {
            // 发现nums2的元素 在nums_set里又出现过
            if (nums_set.find(num) != nums_set.end()) { // 不等于end说明找到了
                result_set.insert(num);
            }
        }
        return vector<int>(result_set.begin(), result_set.end());
    }
};
```

## LeetCode 202.快乐数

### 题目

编写一个算法来判断一个数 `n` 是不是快乐数。

**「快乐数」** 定义为：

- 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
- 然后重复这个过程直到这个数变为 1，也可能是 **无限循环** 但始终变不到 1。
- 如果这个过程 **结果为** 1，那么这个数就是快乐数。

如果 `n` 是 *快乐数* 就返回 `true` ；不是，则返回 `false` 

> **示例 1：**
>
> **输入：**n = 19 **输出：**true **解释：** 1(2) + 9(2) = 82 8(2) + 2(2) = 68 6(2) + 8(2) = 100 1(2) + 0(2) + 0(2) = 1
>
> **示例 2：**
>
> **输入：**n = 2 **输出：**false

### 思路

这道题一开始就是想不断计算，直到某次计算出sum==1，则返回True，但是一直找不到退出循环的条件，因为不是快乐数会无限循环。

主要还是没有想明白：求和的过程中，无限循环就是说sum会**重复出现**。

第二个遇到的问题是计算各位数字平方和时，应该用循环算，不能简单的算两位或者三位。可以写一个函数来实现取得各位数字平方和。

### 代码

```C++
class Solution {
public:
    int getSum(int n) {
        int sum = 0;
        while (n) {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        return sum;
    }
    bool isHappy(int n) {
        unordered_set<int> set;
        int sum = 0;
        while (1) {
            sum = getSum(n);
            if (sum == 1) {
                return true;
            }
            if (set.find(sum) != set.end()) {
                return false;
            } else {
                set.insert(sum);
            }
            n = sum;
        }
    }
};
```

### 时空复杂度

时间复杂度：

1. `getSum`函数计算一个整数的每位数字的平方和。对于一个`k`位数字，这个函数的时间复杂度是`O(k)`。
2. `isHappy`函数是检测快乐数的主要函数。在这个函数中，我们使用`while`循环来不断计算数字的平方和，直到这个和先前已经计算过（即出现在集合`set`中）或者和为1。

最坏情况下，时间复杂度不易直接分析，因为它依赖于数字`n`达到重复数字或者1所需的步骤数。研究表明，对于任意的`n`，这个过程要么最终到达1，要么最终进入一个循环。这个循环并不大，因此这个算法的时间复杂度通常被认为是`O(log n)`.

空间复杂度：unordered_set<int> set用来存储之前计算过的数字平方和，以检测循环。因此，空间复杂度与存储的不同平方和的数量有关。由于快乐数的性质，这个集合的大小会被限制在一个较小的范围内，它不会超过log n数量级的不同数字，所以空间复杂度可以认为是O(log n).

### 学习与小结

1. 要熟悉对取数值各个位上的单数操作；
2. 题眼没有抓到：无限循环就是说sum会**重复出现**。为什么呢？
   1.  考虑以下两点：
   2. **有限的可能性**：对于任何给定的`n`位数字，其平方和的最大可能值发生在其每一位都是9的情况。例如，三位数的最大平方和为`9^2 + 9^2 + 9^2 = 243`。可以观察到，随着数字位数的增加，其平方和实际上可能会变小。因此，对于任何初始数字，平方和计算将总是落在一个有限的集合中。
   3. **迭代过程**：当我们对数字反复进行平方和计算时，每次迭代的结果要么会逐渐减小并最终达到1（快乐数的情况），要么会在某些值之间循环。由于我们知道可能的平方和是有限的，因此如果一个数字不是快乐数，迭代过程总会在已经出现过的平方和值上重复，因为没有无限的不同值可以循环。
   4.  由于这个迭代过程最终必然会落入一个重复的模式，这意味着会有一个`sum`值重复出现。一旦`sum`值重复出现，我们就知道我们已经进入了一个不包括1的循环，从而得出这个数字不是快乐数。实际上，对于不是快乐数的情况，所有的非快乐数最终都会陷入同一个循环，这个循环以4开始，然后是16，37，58，89，145，42，20，4，然后这个模式重复。

## LeetCode 1.两数之和

给定一个整数数组 `nums` 和一个整数目标值 `target`，请你在该数组中找出 **和为目标值** *`target`*  的那 **两个** 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

### 题目

> **示例 1：**
>
> **输入：**nums = [2,7,11,15], target = 9 **输出：**[0,1] **解释：**因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
>
> **示例 2：**
>
> **输入：**nums = [3,2,4], target = 6 **输出：**[1,2]
>
> **示例 3：**
>
> **输入：**nums = [3,3], target = 6 **输出：**[0,1]

### 思路

将nums数组转化成unordered_map，一开始想着下标作为key，数组值作为value，然后发现如果要用find函数的话，只可以搜索key值，所以需要用数组值作为key，下标当作value。另一个要注意的点是**数组中同一个元素在答案里不能重复出现**，示例三中如果不做重复判断，就会返回[0,0]。加上判断后，以示例三为例，当i=0时，通过find函数找到的key-value是[3,0]，此时重复元素，所以不把结果保存，继续循环使i=1，通过find函数找到的key-value是[3,0]，不再重复，满足题意。

### 代码

```C++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map <int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            map[nums[i]] = i;
        }
        vector<int> result;
        for (int i = 0; i < nums.size(); i++) {
            int comp = target - nums[i];
            auto it = map.find(comp);
            if (it != map.end() && it->second != i) {
                result.push_back(i);
                result.push_back(it->second);
                break;
            }
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：主要操作是遍历数组，对于哈希表的操作都是O(1)级别。时间复杂度为O(n).

空间复杂度：

1. **哈希表****存储：** 最坏的情况下（没有两个数的和为`target`），整个数组会被存储在哈希表中。这意味着哈希表中的元素数量最多与数组`nums`的元素数量相同。
2. **输出数组：** 输出数组`result`存储了两个整数，它的空间占用是常数级别的，`O(1)`。

总的空间复杂度是`O(n)`。

### 学习与小结

看了[代码随想录的讲解](https://programmercarl.com/0001.两数之和.html#思路)，发现自己对于本题还是一知半解，并没有真正掌握。

- 为什么会想到用哈希表？
  -  当我们需要查询一个元素是否出现过，或者一个元素是否在集合里的时候，就要第一时间想到哈希法。对于这道题，我的第一想法是，对于当前遍历的元素，要在数组中能否找到一个和他匹配的元素，即`target-nums[i]`是否出现在集合里，正好符合哈希法。
- 哈希表为什么用map？
  -  既要计算两数之和，又需要返回两数在数组的下标，刚好复合map的key-value，所以用map。
- 本题map是用来存什么的？map中的key和value用来存什么的？
  -  我的想法是直接将数组转化成map，数组中元素的值为key，下标为value。而代码随想录的解法是map目的用来存放我们访问过的元素，因为遍历数组的时候，需要记录我们之前遍历过哪些元素和对应的下标，这样才能找到与当前元素相匹配的（也就是相加等于target）。

卡哥的想法是初始map为空，遍历数组时，去map中找是否有能和当前元素匹配的值，如果有，就返回结果，函数结束；如果没有，就把当前遍历的数组加入到map中。这种思路在时间效率上比我的思路更加优化，在一次循环中完成任务，不需要再多一步先将数组转化成map。其次对于重复值的问题（示例3）有了更直接的解决方案。当遍历到第一个3时，map为空，找不到与之匹配的值，所以将[3,0]加入到map中。遍历到第二个3时，在map中找到了与之匹配的值，直接返回结果，逻辑十分顺畅。

```C++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map <int,int> map;
        for(int i = 0; i < nums.size(); i++) {
            // 遍历当前元素，并在map中寻找是否有匹配的key
            auto iter = map.find(target - nums[i]); 
            if(iter != map.end()) {
                return {iter->second, i};
            }
            // 如果没找到匹配对，就把访问过的元素和下标加入到map中
            map.insert(pair<int, int>(nums[i], i)); 
        }
        return {};
    }
};
```