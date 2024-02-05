# 代码随想录算法训练营第三十九天| 动态规划 Part02

## 今日题目

62.[不同路径](https://leetcode.cn/problems/unique-paths/)

63.[不同路径 II](https://leetcode.cn/problems/unique-paths-ii/)

## LeetCode 62.不同路径

### 题目

一个机器人位于一个 `m x n` 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

> 输入：m = 3, n = 7 输出：28
>
> 示例 2：
>
> 输入：m = 3, n = 2 输出：3 解释： 从左上角开始，总共有 3 条路径可以到达右下角。 1. 向右 -> 向下 -> 向下 2. 向下 -> 向下 -> 向右 3. 向下 -> 向右 -> 向下

### 思路

只有两个位置可以到达最终位置，分别是最终位置的上边和左边。所以dp[i][j]表示到达i，j共有几条路，递推公式就是从上边来的路径数加上从左边来的路径数，初始化要让第一行和第一列全为1，因为只可以向右或向下移动。

### 代码

```C++
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for (int i = 0; i < n; i++) {
            dp[0][i] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(mn).

空间复杂度：空间复杂度为O(mn).

## LeetCode 63.不同路径Ⅱ

### 题目

一个机器人位于一个 `m x n` 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

网格中的障碍物和空位置分别用 `1` 和 `0` 来表示。

> 输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]] 输出：2 解释：3x3 网格的正中间有一个障碍物。 从左上角到右下角一共有 2 条不同的路径： 向右 -> 向右 -> 向下 -> 向下 向下 -> 向下 -> 向右 -> 向右

### 思路

基本思路和上题一样，加了障碍物对初始化有一些影响：第一行和第一列初始化时，如果有障碍物当前dp值为1，如果前一个的dp为0，那么说明前一个不可达，此处的dp也应该为0.

### 代码

```C++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            if (obstacleGrid[i][0] == 1) {
                dp[i][0] = 0;
            } else {
                if (i > 0 && dp[i - 1][0] == 0) {
                    dp[i][0] = 0;
                } else {
                    dp[i][0] = 1;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (obstacleGrid[0][i] == 1) {
                dp[0][i] = 0;
            } else {
                if (i > 0 && dp[0][i - 1] == 0) {
                    dp[0][i] = 0;
                } else {
                    dp[0][i] = 1;
                }
            }
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] != 1) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};
```

### 时空复杂度

时间复杂度：时间复杂度为O(m*n).

空间复杂度：空间复杂度为O(m*n).n、m 分别为obstacleGrid 长度和宽度

### 学习与小结

对于初始化：

```C++
vector<vector<int>> dp(m, vector<int>(n, 0));
for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1;
```

先把整个二维数组赋值为0，初始化时遇到障碍物会跳出循环：**注意代码里****for循环****的终止条件，一旦遇到obstacleGrid[i][0] == 1的情况就停止dp[i][0]的赋值1的操作，dp[0][j]同理。**

```C++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if (obstacleGrid[m - 1][n - 1] == 1 || obstacleGrid[0][0] == 1) //如果在起点或终点出现了障碍，直接返回0
            return 0;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
        for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1;
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 1) continue;
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
```

对于每个节点，如果当前节点是障碍物就跳过这次循环，也无需再赋值为0（初始化时已经赋值为0）.