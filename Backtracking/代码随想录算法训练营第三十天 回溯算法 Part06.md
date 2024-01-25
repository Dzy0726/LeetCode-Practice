# 代码随想录算法训练营第三十天| 回溯算法 Part06

## 今日题目

332.[重新安排行程](https://leetcode.cn/problems/reconstruct-itinerary/)

51.[N 皇后](https://leetcode.cn/problems/n-queens/)

37.[解数独](https://leetcode.cn/problems/sudoku-solver/)

## LeetCode 332.重新安排行程

### 题目

给你一份航线列表 `tickets` ，其中 `tickets[i] = [from(i), to(i)]` 表示飞机出发和降落的机场地点。请你对该行程进行重新规划排序。

所有这些机票都属于一个从 `JFK`（肯尼迪国际机场）出发的先生，所以该行程必须从 `JFK` 开始。如果存在多种有效的行程，请你按字典排序返回最小的行程组合。

- 例如，行程 `["JFK", "LGA"]` 与 `["JFK", "LGB"]` 相比就更小，排序更靠前。

假定所有机票至少存在一种合理的行程。且所有的机票 必须都用一次 且 只能用一次。

> 示例 1：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YmU2N2YyOGI1YzJlOGJjZWE3MDZiNTM3MjEyZjQ1NDRfdFpmSjlsUElBS3A0blB5VnFVMlFpSVh2ejQ4bDhqdFVfVG9rZW46Qm5lT2JENnNXb0Z0cmF4MGtlNmNlaTE1bmxoXzE3MDYxNTUzMzk6MTcwNjE1ODkzOV9WNA)
>
> 输入：tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]] 输出：["JFK","MUC","LHR","SFO","SJC"]
>
> 示例 2：
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MzUzZTVkNWYwNGM1ZjM4ZjdmNGZhNDk1NzdmMGZkZGNfQlJJa09uaWZ0WHNlNmNwUklpVnBFcUFVYnBuOU9nMnpfVG9rZW46VExtMGJDV3RNb3lwNEl4U3VPM2NRVXVwbnRkXzE3MDYxNTUzMzk6MTcwNjE1ODkzOV9WNA)
>
> 输入：tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]] 输出：["JFK","ATL","JFK","SFO","ATL","SFO"] 解释：另一种有效的行程是 ["JFK","SFO","ATL","JFK","ATL","SFO"] ，但是它字典排序更大更靠后。

### 思路

我最开始的思路是将出发地的全部目的地加入到一个数组，从数组中选出字母序最小的作为下一站，也就是下一个递归的出发地，由此来进行递归；同时使用used数组来记录哪张“机票”用过了。但是这样的思路会卡在死胡同，比如这个测试用例就会卡在KUL不动。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGFlMTAyYWU4NzgzNGM4NWU1YzlkNmQ2YjRkYTZhYTZfR3R0T2JvS3JFQVRZbVZGOU1yS01IVHl5dG85YUFySlRfVG9rZW46SnpnUGJGeGp0b0VUVW14d1l6R2NRMVlEbmNmXzE3MDYxNTUzMzk6MTcwNjE1ODkzOV9WNA)

### 学习

这道题对于我来说的难点是怎么实现字母序靠前排在前面。

**一个机场映射多个机场，机场之间要靠字母序排列，一个机场映射多个机场，可以使用****std****::unordered_map，如果让多个机场之间再有顺序的话，就是用std::map 或者std::multimap 或者 std::multiset。**

这样存放映射关系可以定义为 `unordered_map<string, multiset<string>> targets` 或者 `unordered_map<string, map<string, int>> targets`。

含义如下：

unordered_map<string, multiset> targets：unordered_map<出发机场, 到达机场的集合> targets;

unordered_map<string, map<string, int>> targets：unordered_map<出发机场, map<到达机场, 航班次数>> targets;

但是使用`unordered_map<string, multiset<string>> targets` 遍历multiset的时候，不能删除元素，一旦删除元素，迭代器就失效了。

为什么要删除元素？为了避免产生死循环，就要把已经飞过的“机票”从map中删掉。

所以用后者可以记录这张机票是否使用，通过控制航班次数的值。如果“航班次数”大于零，说明目的地还可以飞，如果“航班次数”等于零说明目的地不能飞了，而不用对集合做删除元素或者增加元素的操作。

递归三部曲：

1. 参数及返回值：为了控制参数的长度，可以把map定义成全局变量，因为将tickets转化成了map，所以无需传入tickets，只要传入他的长度即可（用来看是否该返回了）；返回值返回bool类型，说明是否找到路径，因为不需要遍历全部的情况，只要有一条路通，就是找到了结果，而且我们事先把tickets转成map，对其进行了字母序的排序，所以不用考虑顺序的问题，只要找到了结果就是答案；
2. 终止条件：有n张机票result的大小为n+1
3. 单层递归逻辑：如果机票没用过就飞这张机票，记得回溯

### 代码

```C++
class Solution {
public:
    unordered_map<string, map<string, int>> map_tickets;
    vector<string> result;
    bool backtracking(int ticketNum) {
        if (result.size() == ticketNum + 1) {
            return true;
        }
        for (pair<const string, int>& t : map_tickets[result.back()]) {
            if (t.second > 0) {
                t.second--;
                result.push_back(t.first);
                if (backtracking(ticketNum)) return true;
                t.second++;
                result.pop_back();
            }
        }
        return false;
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        int ticketNum = tickets.size();
        for (vector<string> vec : tickets) {
            map_tickets[vec[0]][vec[1]]++;
        }
        result.push_back("JFK");
        backtracking(ticketNum);
        return result;
    }
};
```

### 小结

这道题感觉是没有想到用map嵌套map的形式来存放tickets，这样也避免了使用used数组，还能保证修改同步（修改used数组有时候不是同步，可能改多了也可能改少了）。

`map_tickets` 的值是一个内部 `map`，而 `std::map` 默认情况下会根据键的字母顺序进行排序，因为它是基于红黑树实现的一个有序容器。用了一个unordered_map，它的key是无序的，但是它的值是一个map，map的key是有序的，出发机场固定了比如AAA，那么他的值会是<BBB,1>、<CCC,1> 、<DDD,1>，这三个值会按照key来排序。

```C++
for (pair<const string, int& t : map_tickets[result.back()]) {
    // ...
}
```

如果 `result.back()` 是 `AAA`，那么 `t` 将会按照字典序访问 `<BBB,1>`、`<CCC,1>` 和 `<DDD,1>`。这确保了，在 `backtracking` 过程中，总是首先考虑字典序最小的机场作为下一个目的地。这个性质对解决如 **Hierholzer 算法或欧拉路径问题**中保证按照特定顺序访问节点至关重要，并且它确保了最终的行程是按照字典序最小的顺序排列的。

## LeetCode 51.N皇后

### 题目

按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。

**n 皇后问题** 研究的是如何将 `n` 个皇后放置在 `n×n` 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 `n` ，返回所有不同的 **n** **皇后问题** 的解决方案。

每一种解法包含一个不同的 **n 皇后问题** 的棋子放置方案，该方案中 `'Q'` 和 `'.'` 分别代表了皇后和空位。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MzNmZDUyZDFhZmYzN2NiZDU1YWQzMDI4NDJiN2UxMTRfUVdFbk5mSm9WRzliYjBNQkdIQXRYYWg5T2dKQ29jRmJfVG9rZW46VEo3eWJjVEVab212cGh4YkIxSGNGclNSbnJkXzE3MDYxNTUzMzk6MTcwNjE1ODkzOV9WNA)
>
> 输入：n = 4 输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]] 解释：如上图所示，4 皇后问题存在两个不同的解法。

### 思路

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=M2Q3ODBkYTQwOTY3Njg0NGRhMWFkMGFiYzM5MzE1YWRfVXBEVWI1dWtkS3pVekp5MEhZMlNJNE1KWU15cnBNa3ZfVG9rZW46U0czcWJsdlFDb1p5RlN4WFVDV2NpWnZDbkl1XzE3MDYxNTUzMzk6MTcwNjE1ODkzOV9WNA)

for循环遍历的是树的宽度，也就是每个皇后所在的列的位置；递归遍历的是树的深度，也就是每个皇后所在的行的位置。

for循环col，就是将皇后放到第一列、第二列、第三列依次递归找结果，递归参数中有row，就上将皇后放到第row行，叶子节点就是找到的所有结果。所以遍历整个树，返回值为空。

每层的递归逻辑是for循环看哪列可以放，如果可以放就放上皇后，继续递归，递归结束回溯。

要注意棋盘需要初始化。

### 代码

```C++
class Solution {
public:
    vector<vector<string>> result;
    void backtracking(int n, int row, vector<string>& chessBoard) {
        if (row == n) {
            result.push_back(chessBoard);
            return;
        }
        for (int col = 0; col < n; col++) {
            if (isValid(row, col, n, chessBoard)) {
                chessBoard[row][col] = 'Q';
                backtracking(n, row + 1, chessBoard);
                chessBoard[row][col] = '.';
            }
        }
    }
    bool isValid(int row, int col, int n,vector<string> chessBoard) {
        for (int i = 0; i < row; i++) {
            if (chessBoard[i][col] == 'Q') return false;
        }
        for (int i = row - 1, j = col - 1; i >= 0 && j >=0; i--, j--) {
            if (chessBoard[i][j] == 'Q') return false;
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (chessBoard[i][j] == 'Q') return false;
        }
        return true;
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<string> chessBoard(n, string(n, '.'));
        backtracking(n, 0, chessBoard);
        return result;
    }
};
```

### 学习与小结

判断是否合法为什么不判断行呢？因为每行肯定只能放一个，回溯函数中参数有row就控制了每行只能放一个皇后，所以就不用判断行的情况。而且只需要判断二维数组在当前要插入位置之前的位置就行，之后的位置还没有遍历到，所以不需要看。

row这个值只有在传入递归函数才变化，这样就控制了在本层的for循环中row不变，也就是把这一行每一列都试着放上皇后->递归看后续->回溯>

## LeetCode 37.解数独

### 题目

编写一个程序，通过填充空格来解决数独问题。

数独的解法需 **遵循如下规则**：

1. 数字 `1-9` 在每一行只能出现一次。
2. 数字 `1-9` 在每一列只能出现一次。
3. 数字 `1-9` 在每一个以粗实线分隔的 `3x3` 宫内只能出现一次。（请参考示例图）

数独部分空格内已填入了数字，空白格用 `'.'` 表示。

### 思路

这道题不同于之前的回溯，是在一次递归中既要确定行又要确定列，也就是要确定二维数组的一个值，然后在这个值确定的基础上进行下一轮的递归，确定下一个值。所以是二维数组的递归。

N皇后问题是每一行每一列只放一个皇后，所以可以for循环控制列动（但实则是一行内，一次for循环完成一行的遍历），递归控制行（第一行，第二行，第三行），一层就够。

这道题棋盘的每一个位置都要放一个数字（而N皇后是一行只放一个皇后），并检查数字是否合法，解数独的树形结构要比N皇后更宽更深。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=M2QwNjYyN2ExYmVlNTNmOTA1NDYzZDA3ZjkyZDcyY2NfVlRDYzd4MzEyaG55NlljeVo1a254d1dJV1NBaWVwSjhfVG9rZW46WnVSWWJlWEx0b0lVZTh4azJleGMxalFYblBJXzE3MDYxNTUzMzk6MTcwNjE1ODkzOV9WNA)

题目保证数独有唯一解，所以一旦找到该解，就返回，返回类型为BOOL；

本题递归不用终止条件，解数独是要遍历整个树形结构寻找可能的叶子节点就立刻返回。

不用终止条件会不会死循环？

递归的下一层的棋盘一定比上一层的棋盘多一个数，等数填满了棋盘自然就终止（填满当然好了，说明找到结果了），所以不需要终止条件！

如果没找到直接返回false就行，发生某个格子填不进数字的情况就是无解，直接返回false；

一个for循环遍历棋盘的行，一个for循环遍历棋盘的列，一行一列确定下来之后，递归遍历这个位置放9个数字的可能性。

是否合法：看这个数字同行有没有出现、同列有没有出现、3*3的小方格内有没有出现，三者都没有出现就合法。

### 代码

```C++
class Solution {
public:
    bool backtracking(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    continue;
                }
                for (char k = '1'; k <= '9'; k++) {
                    if (isValid(k, i, j, board)) {
                        board[i][j] = k;
                        if (backtracking(board)) return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }

    bool isValid(char n, int row, int col, vector<vector<char>> board) {
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == n) return false;
        }
        for (int i = 0; i < 9;i++) {
            if (board[row][i] == n) return false;
        }
        int startrow = (row / 3) * 3;
        int startcol = (col / 3) * 3;
        for (int i = startrow; i < startrow + 3; i++) {
            for (int j = startcol; j < startcol + 3; j++) {
                if (board[i][j] == n) return false;
            }
        }
        return true;
    }
    void a(vector<vector<char>>& board) {
        backtracking(board);
    }
};
```

### 学习与小结

递归函数中return false的位置要注意，如果一行一列确定下来了，这里尝试了9个数都不行，说明这个棋盘找不到解决数独问题的解，那么会直接返回， 这也就是为什么没有终止条件也不会永远填不满棋盘而无限递归下去。

## 回溯总结

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ODRiNWQyZTkzZjQ2NmJhNGUyY2JmNmU5NjkyMzIzZjFfSTd4MFk2eThoVGFhNFBHalNsM1p5amhNb1dHT25TZk5fVG9rZW46VzROSGJvNnMxb29nN0Z4dFhHbWN2a0N2bnVlXzE3MDYxNTUzMzk6MTcwNjE1ODkzOV9WNA)

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YzQ5NWM0YWQ4ZGRiZTk4NzA5YzFhYjlmMjJhMGQxOGRfUGN5dFd1UkJMNWJKVlFpdkdvb3NnU1RJT2JrV3RNY2xfVG9rZW46VUFjd2JLcFM0b2ZvbzF4ZnRHT2NJOXpPbmdiXzE3MDYxNTUzMzk6MTcwNjE1ODkzOV9WNA)