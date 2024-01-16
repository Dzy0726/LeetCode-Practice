# 代码随想录算法训练营第二十一天| 二叉树 Part07

## 今日题目



530.[二叉搜索树的最小绝对差](https://leetcode.cn/problems/minimum-absolute-difference-in-bst/)

501.[ 二叉搜索树中的众数](https://leetcode.cn/problems/find-mode-in-binary-search-tree/)

236.[二叉树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/)

## LeetCode 530.二叉搜索树的最小绝对差

### 题目

给你一个二叉搜索树的根节点 `root` ，返回 **树中任意两不同节点值之间的最小差值** 。

差值是一个正数，其数值等于两值之差的绝对值。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YTVjYTU0MDYyMzc3YjBlZWUyOTcwZTI3NjdhYjNhN2FfYk13SXpzdHdZVXVvQlVxQU9IMU1qOTZVWGdBbGNSSHVfVG9rZW46QUo5MmJPV0N4bzhOZXp4RUhYdmNtOVRrbmlmXzE3MDUzNzUyMzI6MTcwNTM3ODgzMl9WNA)
>
> 输入：root = [4,2,6,1,3] 输出：1

### 思路

中序遍历二叉搜索树，形成的是一个递增的数组；遍历数组，依次计算vec[i] - vec[i - 1]，不断更新最小值。

### 代码

```C++
class Solution {
public:
    void inorder(TreeNode* root, vector<int> &vec) {
        if (root == NULL) return;
        inorder(root -> left, vec);
        vec.push_back(root -> val);
        inorder(root -> right, vec);    
    }
    int getMinimumDifference(TreeNode* root) {
        vector<int> vec;
        inorder(root, vec);
        int minVal = INT32_MAX;
        for (int i = 1;i < vec.size(); i++) {
            minVal = minVal < (vec[i] - vec[i - 1]) ? minVal : (vec[i] - vec[i - 1]);
        }
        return minVal;
    }
};
```

### 时空复杂度

时间复杂度：

- 中序遍历（`inorder` 函数）访问树中的每个节点一次，因此其时间复杂度是 `O(n)`，其中 `n` 是树中的节点数。
- 之后的循环遍历排序后的数组 `vec` 一次，计算最小差值，其时间复杂度也是 `O(n)`。

所以总的时间复杂度为O(n).

空间复杂度：

- 使用了一个 `vector<int>` 来存储中序遍历的结果，这需要 `O(n)` 的空间来存储 `n` 个节点的值。
- 除了递归调用的栈空间外，没有使用额外的空间。递归调用的栈空间在最坏的情况下（树完全倾斜时）也为 `O(n)`。

所以总的空间复杂度是 `O(n)`。

### 学习与小结

二叉搜索树中序遍历会形成单调递增的数组，其实在二叉遍历过程中，如果能找到当前节点值和它前一个节点的值比较，就可以省去形成数组再遍历数组的过程：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZDMwNjUzOGRmNDIxODBiNjkzMDU1MzYxY2QzMTU4MjFfNXFheW9FMG5WQXJNQ0lYMHBacmlIalhmQ1ZvRU83UlVfVG9rZW46QU13QWJXVVlBb1g5REF4SFdBdWNlU2NBbktHXzE3MDUzNzUyMzI6MTcwNTM3ODgzMl9WNA)

又见“双指针”~用pre记录当前节点的上一个节点，就是在每次中序遍历处理完中间节点，将cur赋值给pre，cur继续遍历，比较cur与pre的节点值大小。

```C++
class Solution {
public:
    int result = INT32_MAX;
    TreeNode* pre = NULL;
    void inorder(TreeNode* cur) {
        if (cur == NULL) return;
        inorder(cur -> left);
        if (pre != NULL) {
            result = min(result, cur -> val - pre -> val);
        }
        pre = cur;
        inorder(cur -> right);
    }
    int getMinimumDifference(TreeNode* root) {
        inorder(root);
        return result;
    }
};
```

## LeetCode 501.二叉搜索树中的众数

### 题目

给你一个含重复值的二叉搜索树（BST）的根节点 `root` ，找出并返回 BST 中的所有 [众数](https://baike.baidu.com/item/众数/44796)（即，出现频率最高的元素）。

如果树中有不止一个众数，可以按 **任意顺序** 返回。

假定 BST 满足如下定义：

- 结点左子树中所含节点的值 **小于等于** 当前节点的值
- 结点右子树中所含节点的值 **大于等于** 当前节点的值
- 左子树和右子树都是二叉搜索树

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZjU1ODU5YjhiN2E5MDJkMjNlMWNhMWVlZDc3NDYwZGZfSVRQeVFxN1dJcGdWaHRlR05RdWU0cHU2ZklRd09PM05fVG9rZW46Q2ZOb2JQS0ZUb241MDh4dGc4Z2NRRkFLbjNtXzE3MDUzNzUyMzI6MTcwNTM3ODgzMl9WNA)
>
> 输入：root = [1,null,2,2] 输出：[2]

### 思路

将每个元素及其出现的次数保存到一个map中，然后将map转为vector，对vector进行排序。（算是对前k个高频元素解法一的复习）排序后先把vec第一个加入result，遍历vec，如果有和vec[0]频率一样的，也加入result。

### 代码

```C++
class Solution {
public:
    static bool compare(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    }
    void inorder(TreeNode* root, unordered_map<int, int> &map) {
        if (root == NULL) return;
        inorder(root -> left, map);
        map[root -> val]++;
        inorder(root -> right, map);
    }
    vector<int> findMode(TreeNode* root) {
        unordered_map<int, int> map;
        vector<int> result;
        inorder(root, map);
        vector<pair<int, int>> vec(map.begin(), map.end());
        sort(vec.begin(), vec.end(), compare);
        result.push_back(vec[0].first);
        for (int i = 1; i < vec.size(); i++) {
            if (vec[i].second == vec[0].second) {
                result.push_back(vec[i].first);
            }
        }
        return result;
    }
};
```

### 时空复杂度

时间复杂度：

1. 中序遍历：`inorder` 函数递归地访问了树中的每个节点一次，其时间复杂度为 `O(n)`，其中 `n` 是树中的节点数目。
2. 构造 `vector`：将 `unordered_map` 转换成 `vector` 的操作为 `O(n)`，因为需要遍历映射中的所有元素。
3. 排序：`sort` 函数对 `vector` 进行排序，时间复杂度为 `O(n log n)`，因为使用了比较排序算法（快速排序、归并排序等）。
4. 查找众数：遍历已排序的 `vector`，时间复杂度为 `O(n)`，因为在最坏情况下可能需要遍历整个数组。

综上，总的时间复杂度为 `O(n) + O(n) + O(n log n) + O(n) = O(n log n)`，其中排序占据了主导。

空间复杂度：

1. `unordered_map`：存储每个值及其出现次数，最多有 `n` 个不同的值，因此空间复杂度为 `O(n)`。
2. `vector<pair<int, int>>`：存储 `unordered_map` 中的元素，空间复杂度同样为 `O(n)`。
3. 递归栈空间：`inorder` 函数的递归调用在最坏情况下（树完全倾斜时）的空间复杂度为 `O(n)`。
4. `vector<int> result`：在最坏情况下（所有节点值相等时），存储结果需要的空间也为 `O(n)`。

综上，总的空间复杂度为 `O(n) + O(n) + O(n) = O(n)`，主要是存储值及其出现次数和递归栈的空间。

需要注意的是，在实际应用中，如果二叉树是平衡的，则递归栈的空间复杂度会降低到 `O(log n)`，

### 学习与小结

我的解法对任何二叉树都适用，没有用到二叉搜索树的性质：中序遍历有序。也就是说重复元素一定是相邻的几个元素。那么就可以用双指针，看中序遍历中相邻的元素是否相等，如果相等就让统计频率count++，如果count大于等于maxcount，就将当前值加入到结果数组中。

那么如何保证当前maxcount一定是整个二叉树的最大maxcount呢？保证不了，所以**每次maxcount更新时，将结果数组清空**。

```C++
class Solution {
public:
    vector<int> result;
    TreeNode* pre = NULL;
    int maxcount = 0;
    int count = 0;
    void inorder(TreeNode* cur) {
        if (cur == NULL) return;
        inorder(cur -> left);
        if (pre == NULL) { // 第一个节点count = 1
            count = 1;
        } else if (pre -> val == cur -> val) {
            count++;
        } else { // 前后不相等 count重置为1
            count = 1;
        }
        pre = cur;
        if (count == maxcount) {
            result.push_back(cur -> val);
        }
        if (count > maxcount) {
            maxcount = count;
            result.clear();
            result.push_back(cur -> val);
        }
        inorder(cur -> right);
    }
    vector<int> findMode(TreeNode* root) {
        count = 0;
        maxcount = 0;
        pre = NULL;
        result.clear();
        inorder(root);
        return result;
    }
};
```

## LeetCode 236.二叉树的最近公共祖先

### 题目

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

[百度百科](https://baike.baidu.com/item/最近公共祖先/8918834?fr=aladdin)中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YmQxZjVkZTMwYjYzMmQ1NjBhZjc2ODBkOTIzOWZlNDhfaEpEOVowak9KRTB3TVVOWUJEWm11Tmg0dTVKZjI1b0hfVG9rZW46UnhXRmJqek9wb1BwWGN4cEZDWmNoTzFqblBjXzE3MDUzNzUyMzI6MTcwNTM3ODgzMl9WNA)
>
> ```Plaintext
> 输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
> 输出：3
> 解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
> ```

### 思路

找到p、q两个节点的全部祖先，然后比较，找出最近的公共祖先。实现一个函数寻找给定节点的全部祖先，有点像寻找路径那道题，将给定节点的全部祖先保存到一个队列中。然后比较两个队列的头元素，如果相等就更新result，然后删除两个队列的头元素（说明有公共祖先，但是不能保证是最小公共祖先）。如果循环结束，说明找到了最小公共祖先或者没有找到祖先。

自己写的时候回溯还是没弄明白，这块要加深理解记忆。

### 代码

```C++
class Solution {
public:
    bool findAncestor(TreeNode* root, TreeNode *p, deque<TreeNode*> &pAncestor) {
        if (root == NULL) return false;
        pAncestor.push_back(root);
        if (root == p) return true;
        if (findAncestor(root -> left, p, pAncestor) || findAncestor(root -> right, p, pAncestor)) {
            return true;
        }
        pAncestor.pop_back();
        return false;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        deque<TreeNode*> pAncestor;
        deque<TreeNode*> qAncestor;
        findAncestor(root, p, pAncestor);
        findAncestor(root, q, qAncestor);
        TreeNode * result;
        while (!pAncestor.empty() && !qAncestor.empty() && pAncestor.front() == qAncestor.front()) {
            result = pAncestor.front();
            pAncestor.pop_front();
            qAncestor.pop_front();
        }
        return result;
    }
};
```

### 学习与小结

如果在遍历树时，从子树中找到了两个节点 `p` 和 `q`，则该子树的根节点就是 `p` 和 `q` 的最低公共祖先。

最直观的情况如：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=OTNkNWZlOTg2NTZjYWQ3MjI0ZGI1YzJjMjUyZWE5MmNfbVpCR0JtUUJ6OWo2eVVLZ1Nnb09SeU9TQ0RpOG82bVlfVG9rZW46R3NoN2JwcXh6b010Rmh4ZllVNGN6eWFObnRmXzE3MDUzNzUyMzI6MTcwNTM3ODgzMl9WNA)

p和q正好是一个节点的左右孩子，那么显然该节点就是要求的最近的公共祖先。我们进行一下拓展：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NTNhMzJjMmQ5ZWQ3OGQyOTk0ODBjOTU1NzdhMDNmZWZfcUU1YlV5SnZvVDNGUDlCN05xd0VMOWJCNGFsWVBrbE5fVG9rZW46SW9SU2I2QkF2b05Fb1N4WU15bWNqemxobkdnXzE3MDUzNzUyMzI6MTcwNTM3ODgzMl9WNA)

如果p和q分别为6和9，那么2是其最近公共祖先。6和9分别在2的左子树和右子树中，即使6和9不在同一层，比如9在下一层，最终的结果也是2。再次理解这句话：

如果在遍历树时，从子树中找到了两个节点p和q，则该子树的根节点就是p和q的最低公共祖先。

无论是第一种情况，4是3和1的“直接”父节点；还是第二种情况，6和9分别是2的左子树和右子树中的节点，只要在某个子树中找到了两个节点，这个子树的根节点就是p和q的最低公共祖先。

再比如：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YjY3Y2Q3ZjRlZWNmNzg2MTdhYzliOWMxNGEwMDgzNGJfS2NVbXZ6RFd4RTZZY2hmWmRUTW1NTzJET1dRWWpONnJfVG9rZW46WjNlcWJrblI5b0dWVmJ4Z1FJbmN6TlVDbnNnXzE3MDUzNzUyMzI6MTcwNTM3ODgzMl9WNA)

在子树431中找到了4和3，那么根节点4就是最低公共祖先。

据此，我们可以有思路：递归遍历树，记录每个节点的左孩子和右孩子，如果两个孩子都有返回值，那么该节点就是要求的最低公共祖先。

递归三部曲：

1. 参数及返回值：参数传入两个目标节点和当前的节点作为根节点，返回类型为TreeNode*；
2. 终止条件：当前节点为NULL，返回NULL；当前节点是p或q返回p或q；
3. 单层递归逻辑：在递归函数有返回值的情况下：如果要搜索一条边，递归函数返回值不为空的时候，立刻返回，如果搜索整个树，直接用一个变量left、right接住返回值，这个left、right后序还有逻辑处理的需要，也就是后序遍历中处理中间节点的逻辑（也是回溯）。

- 如果 `left` 和 `right` 都不为空，这意味着在当前节点的两侧各找到了一个节点（`p` 和 `q`），所以当前节点就是 LCA。
- 如果 `left` 为空而 `right` 不为空，这意味着两个节点都在右侧，返回 `right`。
- 如果 `right` 为空而 `left` 不为空，这意味着两个节点都在左侧，返回 `left`。
- 如果 `left` 和 `right` 都为空，这意味着在当前分支中没有找到任何节点，返回 `NULL`。

```C++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || root == p || root == q ) return root;
        TreeNode * left = lowestCommonAncestor(root -> left, p, q);
        TreeNode * right = lowestCommonAncestor(root -> right, p ,q);
        if (left != NULL && right != NULL) return root;
        if (left == NULL && right != NULL) return right;
        else if (left != NULL && right == NULL) return left;
        else return NULL;
    }
};
```

关于回溯法，加强理解记忆：

1. 首先，函数接收三个参数：当前节点 `root`，目标节点 `p` 和用于存储祖先节点的队列 `pAncestor`。
2. 如果当前节点 `root` 是 `NULL`，则表示到达了树的末端而没有找到目标节点，因此返回 `false`。
3. 将当前节点 `root` 添加到祖先队列 `pAncestor` 中，因为 `root` 可能是到达目标节点路径上的一个节点。
4. 接下来检查当前节点是否是目标节点 `p`。如果是，我们已经找到了路径，返回 `true`。
5. 如果当前节点不是目标节点，则递归地调用 `findAncestor` 函数在左子节点和右子节点上继续搜索目标节点 `p`。

```Plaintext
if (findAncestor(root->left, p, pAncestor) || findAncestor(root->right, p, pAncestor)) {
    return true;
}
```

1. 如果在当前节点的左子树或右子树中找到目标节点 `p`，递归调用将返回 `true`，并且递归过程终止。在这种情况下，由于已经找到路径，因此当前节点 `root` 应该留在 `pAncestor` 中。
2. 如果当前节点的左右子树都没有找到目标节点 `p`，这意味着当前节点不是目标节点 `p` 的祖先。此时，我们需要回溯：将当前节点从祖先队列 `pAncestor` 中移除，这通过 `pop_back` 操作完成。
3. 最后，返回 `false` 表示从当前节点的子树中没有找到目标节点 `p`。