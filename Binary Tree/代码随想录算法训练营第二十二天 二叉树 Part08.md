# 代码随想录算法训练营第二十一天| 二叉树 Part08

## 今日题目

235.[二叉搜索树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/)

701.[二叉搜索树中的插入操作](https://leetcode.cn/problems/insert-into-a-binary-search-tree/)

450.[删除二叉搜索树中的节点](https://leetcode.cn/problems/delete-node-in-a-bst/)

## LeetCode 235. 二叉搜索树的最近公共祖先

### 题目

给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

[百度百科](https://baike.baidu.com/item/最近公共祖先/8918834?fr=aladdin)中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”

例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGU5NjE0MTY1NmI3NDRiMzdmM2U5OTFkOTgwMGViOTlfd0xBYkNWWUQ2NHB6Rlo4OWZzNHRueGxCTnlkMmpCRndfVG9rZW46TUdPVmJURVhFb1JaNER4UE90S2NhcktlbndiXzE3MDU0ODU4NzY6MTcwNTQ4OTQ3Nl9WNA)

> ```Plaintext
> 输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
> 输出: 6 
> 解释: 节点 2 和节点 8 的最近公共祖先是 6。
> ```

### 思路

上来先假装看不到搜索二字，直接复习昨天学的找二叉树的公共祖先，很快AC哈哈。

那么二叉搜索树，如何利用其特性呢？二叉搜索树是有序的，左<中<右，那么找到一个公共祖先，必定是在两个节点的范围内（闭区间）。比如上面的示例，6是在[2, 8]内；再选0和5两个节点，他们的最小公共祖先是2, 2也在[0,5]内；换一种特殊情况，选择节点7和8，它们的最小公共祖先也在范围[7, 8]内。

现在确定了公共祖先的值一定是在两个节点范围内的，那么如何确定找到最小的呢？

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=YmZjMGFhNGE4YWNjM2Q2MTEyYzg1MDkwYjU3ZTJlNGJfYmdJZGZKRTM1OFdCVUN1cndWSTZreDJaOEoxMkwxcThfVG9rZW46QWNLVmIzRXRNb0RJYmt4THlOSGN6RzNNbjdiXzE3MDU0ODU4NzY6MTcwNTQ4OTQ3Nl9WNA)

我们从根节点搜索，第一次遇到 cur节点是数值在[q, p]区间中，即节点5，此时可以说明 q 和 p 一定分别存在于节点 5的左子树和右子树中。此时节点5是不是最近公共祖先？ 如果从节点5继续向左遍历，那么将错过成为p的祖先， 如果从节点5继续向右遍历则错过成为q的祖先。

所以当我们从上向下去递归遍历，第一次遇到 cur节点是数值在[q, p]区间中，那么cur就是q和p的最近公共祖先。

递归三部曲：

1. 参数和返回值：参数为当前节点， p，q；返回公共祖先，所以返回类型是TreeNode*；
2. 终止条件：题目中说了p、q 为不同节点且均存在于给定的二叉搜索树中。也就是说一定会找到公共祖先的，所以并不存在遇到空的情况，可以不设置终止条件；
3. 单层递归逻辑：当前节点值大于较大的节点值，递归左子树；小于较小的节点值，递归右子树。（不需要比出哪个是较大值较小值，只要大于两个，或者小于两个，就可以）

### 代码

```C++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root -> val > p -> val && root -> val > q -> val) {
            return lowestCommonAncestor(root -> left, p, q);
        } else if (root -> val < p -> val && root -> val < q -> val) {
            return lowestCommonAncestor(root -> right, p, q);
        } else {
            return root;
        }
    }
};
```

### 学习与小结

迭代法也非常简单，在一个循环内，大就让root去左子树，小就让root去右子树，在区间内，就返回root：

```C++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while(root) {
            if (root->val > p->val && root->val > q->val) {
                root = root->left;
            } else if (root->val < p->val && root->val < q->val) {
                root = root->right;
            } else return root;
        }
        return NULL;
    }
};
```

## LeetCode 701.二叉搜索树中的插入操作

### 题目

给定二叉搜索树（BST）的根节点 `root` 和要插入树中的值 `value` ，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 输入数据 **保证** ，新值和原始二叉搜索树中的任意节点值都不同。

**注意**，可能存在多种有效的插入方式，只要树在插入后仍保持为二叉搜索树即可。 你可以返回 **任意有效的结果** 。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=Y2U2OTk3NWQzYTFjYmEwNmMwNjk3OWE2MTg5Y2RiNDVfZm9pSDRTZGdSWjFFVTN1aWNSamJPYVhBSGFwV0IxdVZfVG9rZW46TWZDUWIzYjIzb2pYcFd4SkVvdGNvRFVpblpkXzE3MDU0ODU4NzY6MTcwNTQ4OTQ3Nl9WNA)
>
> 输入：root = [4,2,7,1,3], val = 5 输出：[4,2,7,1,3,5]

### 思路

迭代法遍历二叉树找到插入位置，插入即可。遍历二叉树时，如果当前节点的值大于要插入的值，就遍历左子树；如果当前节点值小于要插入的值，就遍历右子树。最后判断一下应该插入到左侧还是右侧。要注意细节，比如树初始为空。

### 代码

```C++
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode* newNode = new TreeNode(val);
        if (root == NULL) return newNode;
        TreeNode* cur = root;
        while (cur -> left || cur -> right) {
            if (val < cur -> val && cur -> left != NULL) {
                cur = cur -> left;
            } else if (val > cur -> val && cur ->right != NULL) {
                cur = cur -> right;
            } else {
                break;
            }
        }
        if (val < cur -> val) {
            cur -> left = newNode;
        } else {
            cur -> right = newNode;
        }
        return root;
    }
};
```

### 学习与小结

如何用递归法来做？

递归三部曲：

1. 参数及返回类型：参数包括当前传入节点，和要插入的值，返回类型为TreeNode*
2. 终止条件，如果当前节点为空，就用要插入的值构造新节点，返回；
3. 单层递归逻辑：如果当前节点为空，说明到了要插入的位置，构建新节点插入返回；如果不空，比较当前节点和要插入的值的大小，当前节点值更大，就递归遍历左子树；当前节点值更小，就递归遍历右子树。

```C++
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == NULL) {
            TreeNode * node = new TreeNode(val);
            return node;
        }
        if (root -> val > val) {
            root -> left = insertIntoBST(root -> left, val);
        } else {
            root -> right = insertIntoBST(root -> right, val);
        }
        return root;
    }   
};
```

## LeetCode 450.删除二叉搜索树中的节点  

### 题目

给定一个二叉搜索树的根节点 **root** 和一个值 **key**，删除二叉搜索树中的 **key** 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。

一般来说，删除节点可分为两个步骤：

1. 首先找到需要删除的节点；
2. 如果找到了，删除它。

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NDllMjA3ZGIwYjZlZDBkZGYxODAwNDlkMmE3ZDM0MDRfYktVQmNSSXd2bzVjTm1UNzlhcUIxZUYyVzZCc3dDV1lfVG9rZW46SHVHTGJabzY2b09Fcll4RXlKbWN5REloblZiXzE3MDU0ODU4NzY6MTcwNTQ4OTQ3Nl9WNA)
>
> 输入：root = [5,3,6,2,4,null,7], key = 3 输出：[5,4,6,2,null,null,7] 解释：给定需要删除的节点值是 3，所以我们首先找到 3 这个节点，然后删除它。 一个正确的答案是 [5,4,6,2,null,null,7], 如下图所示。 另一个正确答案是 [5,2,6,null,4,null,7]。

### 思路

使用迭代法，pre记录当前节点的前一个节点，cur记录当前节点，首先在树中找到要删除的节点，此时cur指向要删除的节点，pre指向cur的父节点。如果循环结束cur为空，说明要删除的值不在树中，返回root即可。

找到要删除的节点后，分情况讨论：

1. 如果该节点是叶子节点，通过比较得知它是pre的左孩子还是右孩子，然后直接删去即可；
2. 如果该节点是非叶子节点且它只有左孩子或者右孩子，直接把左孩子或者有孩子给到它的父节点即可；
3. 如果该节点是非叶子节点且它既有左孩子又有右孩子，整体思路是把它的左孩子“过继”给它的右孩子，再把它的右孩子“过继”给它的父节点。细节操作的话要注意找到它右孩子的最左下的节点作为它左孩子的父亲。
4. 如果该节点是根节点，经历上述操作后，返回根节点的右孩子即可。

代码判断非常多，应该是没找到最简洁的思路，但是好在把这道题AC了，故作记录。

### 代码

```C++
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == NULL) return root;
        TreeNode * pre = root;
        TreeNode * cur = root;
        while (cur) {
            if (cur -> val > key) {
                pre = cur;
                cur = cur -> left;
            } else if (cur -> val < key) {
                pre = cur;
                cur = cur -> right;
            } else {
                break;
            }
        }
        if (cur == NULL) {
            return root;
        }
        if (cur -> left == NULL && cur -> right == NULL) {
            if (cur -> val < pre -> val) {
                pre -> left = NULL;
            } else {
                pre -> right = NULL;
            }
        } else if (cur -> left == NULL && cur -> right != NULL) {
            if (cur -> val < pre -> val) {
                pre -> left = cur -> right;
            } else {
                pre -> right = cur -> right;
            } 
        } else if (cur -> left != NULL && cur -> right == NULL) {
            if (cur -> val < pre -> val) {
                pre -> left = cur -> left;
            } else {
                pre -> right = cur -> left;
            } 
        } else {
            TreeNode * right = cur -> right;
            while (right -> left) {
                right = right -> left;
            }
            right -> left = cur -> left;
            if (cur -> val < pre -> val) {
                pre -> left = cur -> right;
            } else {
                pre -> right = cur -> right;
            } 
        }
        if (cur == root) {
            return root -> right;
        }
        return root;
    }
};
```

### 学习与小结

没想到我的思路居然是正确的！只不过使用了迭代法略显复杂，卡哥总结如下：

> 这里最关键的逻辑就是第五种情况（删除一个左右孩子都不为空的节点），这种情况一定要想清楚。
>
> 而且就算想清楚了，对应的代码也未必可以写出来，所以这道题目既考察思维逻辑，也考察代码能力。
>
> 递归中我给出了两种写法，推荐大家学会第一种（利用搜索树的特性）就可以了，第二种递归写法其实是比较绕的。
>
> 最后我也给出了相应的迭代法，就是模拟递归法中的逻辑来删除节点，但需要一个pre记录cur的父节点，方便做删除操作。
>
> 迭代法其实不太容易写出来，所以如果是初学者的话，彻底掌握第一种递归写法就够了。

练就有效！卡哥提到的第五种情况我也是正确写出，通过画图理清了逻辑，比较开心。

递归三部曲：

1. 参数和返回类型：参数包括当前传入的节点，要删除的值；返回类型为TreeNode*；
2. 终止条件：如果当前节点为空，说明key不在树中，返回root；
3. 单层递归逻辑：就是我在思路中写的分情况讨论部分，下面直接引用卡哥的分类讨论作为学习：

> 有以下五种情况：
>
> - 第一种情况：没找到删除的节点，遍历到空节点直接返回了
> - 找到删除的节点
>   - 第二种情况：左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
>   - 第三种情况：删除节点的左孩子为空，右孩子不为空，删除节点，右孩子补位，返回右孩子为根节点
>   - 第四种情况：删除节点的右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为根节点
>   - 第五种情况：左右孩子节点都不为空，则将删除节点的左子树头结点（左孩子）放到删除节点的右子树的最左面节点的左孩子上，返回删除节点右孩子为新的根节点。

```C++
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root; // 第一种情况：没找到删除的节点，遍历到空节点直接返回了
        if (root->val == key) {
            // 第二种情况：左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
            if (root->left == nullptr && root->right == nullptr) {
                ///! 内存释放
                delete root;
                return nullptr;
            }
            // 第三种情况：其左孩子为空，右孩子不为空，删除节点，右孩子补位 ，返回右孩子为根节点
            else if (root->left == nullptr) {
                auto retNode = root->right;
                ///! 内存释放
                delete root;
                return retNode;
            }
            // 第四种情况：其右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为根节点
            else if (root->right == nullptr) {
                auto retNode = root->left;
                ///! 内存释放
                delete root;
                return retNode;
            }
            // 第五种情况：左右孩子节点都不为空，则将删除节点的左子树放到删除节点的右子树的最左面节点的左孩子的位置
            // 并返回删除节点右孩子为新的根节点。
            else {
                TreeNode* cur = root->right; // 找右子树最左面的节点
                while(cur->left != nullptr) {
                    cur = cur->left;
                }
                cur->left = root->left; // 把要删除的节点（root）左子树放在cur的左孩子的位置
                TreeNode* tmp = root;   // 把root节点保存一下，下面来删除
                root = root->right;     // 返回旧root的右孩子作为新root
                delete tmp;             // 释放节点内存（这里不写也可以，但C++最好手动释放一下吧）
                return root;
            }
        }
        if (root->val > key) root->left = deleteNode(root->left, key);
        if (root->val < key) root->right = deleteNode(root->right, key);
        return root;
    }
};
```

递归法的第五种情况直接返回root->right，统一了要删除节点是根节点的情况，因为在找到的情况下，参数root就是找到的要删除的节点，所以它如果同时有左右孩子，就把左孩子过继给右孩子，返回它的右孩子。