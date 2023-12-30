# 代码随想录算法训练营第四天| 链表 Part02

## 今日题目

24.[两两交换链表中的节点](https://leetcode.cn/problems/swap-nodes-in-pairs/)

19.[删除链表的倒数第 N 个结点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/)

面试题02.07.[链表相交](https://leetcode.cn/problems/intersection-of-two-linked-lists-lcci/)同160.[相交链表](https://leetcode.cn/problems/intersection-of-two-linked-lists/)

142.[环形链表 II](https://leetcode.cn/problems/linked-list-cycle-ii/)

## LeetCode 24. 两两交换链表种的节点

### 题目

给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

> **示例 1：**
>
> **输入：**head = [1,2,3,4] **输出：**[2,1,4,3]
>
> **示例 2：**
>
> **输入：**head = [] **输出：**[]
>
> **示例 3：**
>
> **输入：**head = [1] **输出：**[1]

### 思路

刚开始并没有想到要用虚拟头节点，在画图的过程中发现如果没有虚拟头节点好像还要单独处理head的问题，于是先引入了虚拟头节点。

接着画图，试图找到可以统一起来的操作。因为涉及到很多next指针，一时间想不清楚结束循环的条件，所以遍历了一次链表找出其长度，因为要两两交换，所以用size/2就可以得到交换的次数，用次数来作为结束循环的条件就不用再考虑指针是否为空的问题（当然前提是循环内对于链表节点的操作全部正确）。经过不断的画图，终于发现了几次交换的共同之处，按照我的思路其实一次交换分成两步走，第一步是将dummyhead->1->2->3变成dummyhead->2->3, 1->2；第二步是将1->2变成2->1，整体变成dummyhead->2->1->3。按逻辑写成代码一次AC。

代码可以通过，但显然不是最好的，还需要学习一下更简洁的思路，将自己的思路优化。

### 代码

```C++
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode * dummy = new ListNode();
        dummy -> next = head;
        ListNode * current = new ListNode();
        current = dummy;
        int size = 0;
        int flag = 0;
        ListNode * post = new ListNode();
        while (current -> next) {
            current = current -> next;
            size++;
        }
        current = dummy;
        size = size / 2; 
        while (size--) {
            post = current -> next;
            current -> next = post -> next;
            current = post;
            post = current -> next;
            current -> next = post -> next;
            post -> next = current;
        }
        return dummy->next;
    }
};
```

### 时空复杂度

时间复杂度：循环过程中每个节点遍历了一次，时间复杂度为O(n).

空间复杂度：新建了几个ListNode节点，所以空间复杂度为O(1).

### 学习与小结

1. 操作某个节点的指向，一定要知道它的前一个节点的指针。当前操作的指针必须要指向要反转的两个节点的前一个节点。
2. 交换的过程稍不注意就会出现断链，会有元素丢失，所以在每次交换要确保两步都做到，既交换了两个节点，又与后面的节点仍然保持相连。
3. 什么时候结束循环：当链表节点个数为偶数时，`current->next`为空，就结束循环；为奇数时，`current->next->next`为空就结束了。所以可以写成
   1.  `while (current->next != NULL && current->next->next != NULL)`
   2.  “与”的判断逻辑必须两个条件都得满足，当第一个条件不满足时，结果已经为“0”，就不会去判断第二个条件，所以不用担心`current->next->next`访问空指针。总体来说，控制循环结束的思路和我想到的是差不多的，但是我没有更细节的去用指针来控制。
4. 多用tmp来存放访问不到的一些节点可以减少思考量，避免出错。或许可以先多写几个tmp，最后再按需求删掉多余的tmp。卡哥的代码用了两个tmp来保存后续要访问的位置，第一个tmp就是我代码中用到的post，第二个tmp简化了我后续的移动操作，思考量减少。
5. current指向要交换的两个节点的前一个节点，这句话作为中心思想，在每两个节点交换后，直接让current向后移动两位即可，不仅代码简洁，思考量也减少了很多。反观我的代码中，current和post不停移动，一不小心就容易出错。
6. 从以下代码也可以看出判断条件的巧妙之处：正好在判断`cur->next != nullptr && cur->next->next != nullptr`后，循环中也用到了`cur->next->next`；所以既要避免访问空指针，又要不害怕使用->next->next；只要判断条件控制好，就不会访问到空指针。反而代码直接反映思路，步骤一二三非常清晰。

```C++
class Solution {public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
        dummyHead->next = head; // 将虚拟头结点指向head，这样方便后面做删除操作
        ListNode* cur = dummyHead;
        while(cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* tmp = cur->next; // 记录临时节点
            ListNode* tmp1 = cur->next->next->next; // 记录临时节点
            cur->next = cur->next->next;    // 步骤一
            cur->next->next = tmp;          // 步骤二
            cur->next->next->next = tmp1;   // 步骤三
            cur = cur->next->next; // cur移动两位，准备下一轮交换
         }
         return dummyHead->next;
    }
};
```

## LeetCode 19.删除链表的倒数第N个节点

### 题目

给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。

> **示例 1：**
>
> **输入：**head = [1,2,3,4,5], n = 2 **输出：**[1,2,3,5]
>
> **示例 2：**
>
> **输入：**head = [1], n = 1 **输出：**[]
>
> **示例 3：**
>
> **输入：**head = [1,2], n = 1 **输出：**[1]

### 思路

如果不限制一次遍历解答的话，可以先第一次遍历求出链表长度，然后定位到要删除元素的前一个元素，再将其删除。在这里加入了虚拟头节点，统一操作，无需再单独处理要删除的节点是头节点的情况。

如果要在一次遍历之内解答，没有想到解法。

### 代码

```C++
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode * dummy = new ListNode();
        dummy -> next = head;
        ListNode * current = dummy;
        int size = 0;
        while (current -> next) {
            current = current -> next;
            size++;
        }
        current = dummy;
        int count = size - n;
        while (count--) {
            current = current->next;
        }
        current -> next = current -> next -> next;
        return dummy->next;
    }
};
```

### 时空复杂度

时间复杂度：最坏情况循环过程中每个节点遍历了两次，时间复杂度为O(n).

空间复杂度：新建了几个ListNode节点，所以空间复杂度为O(1).

### 学习与小结

这题好的一点是牢记操作某个节点，一定要有指针指向它的前一个节点。但是又忘记了双指针的应用。

这道题的**双指针法**真是非常的巧妙！快指针先走n步，然后快慢指针一起走，当快指针为空时，说明走到了末尾，那么此时慢指针指向的节点就是要删除的节点，也是倒数第n个节点。再加上要操作某个几点，就要有一个指针指向它前面的那个节点，所以可以让快指针先走n+1步。这样的话，当快指针指向末尾null时，慢指针所指的就是要删除节点的前一个节点，直接删除即可。

```C++
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode * dummy = new ListNode();
        dummy -> next = head;
        ListNode * current = dummy;
        ListNode * fast = current -> next;
        while (n--) {
            fast = fast ->next;
        }
        while (fast) {
            fast = fast ->next;
            current = current -> next;
        }
        current -> next = current -> next -> next;
        return dummy->next;
    }
};
```

## 面试题02.07.链表相交

### 题目

给你两个单链表的头节点 `headA` 和 `headB` ，请你找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 `null` 。

图示两个链表在节点 `c1` 开始相交**：**

> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=N2Q3ZDg5NTgwMDE3M2M1YzAzOGQ1YjM1NDFiNmE3MzlfU3FmUVcxVWVXVkk1TW95bW1lT2lnUUlJb0xKQjVYaXZfVG9rZW46VzQySGJrQXRCb0V4VFV4eTRTaGNWaGU4blBjXzE3MDM5NjE0OTM6MTcwMzk2NTA5M19WNA)
>
> 题目数据 **保证** 整个链式结构中不存在环。
>
> **注意**，函数返回结果后，链表必须 **保持其原始结构** 。
>
>  
>
> **示例 1：**
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=NTM0YWM3MmZkNmE0MzM3MzQ5NDg4MDUzNjBmYWFmZjNfdlJGY0w2OW5lUDUwMjMyekUwWUh6T0RQdlpHc2pBYWlfVG9rZW46UzN1b2JaNzJjb0tXY1d4WURQRWNndzY1bkxoXzE3MDM5NjE0OTM6MTcwMzk2NTA5M19WNA)
>
> **输入：**intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3 **输出：**Intersected at '8' **解释：**相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。 从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。 在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
>
> **示例 2：**
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=MWI2Y2VmZGY1OWIzMjlhYWU2NDI0OTc1YWVkYTMxNWJfbEdaVHBxeTA5MFFFY3dTMmt0YWZyRXlTY0lVbmNjbDhfVG9rZW46SmhNbWJEbHVobzNaT0h4RzJpZGNGWWxRbnZkXzE3MDM5NjE0OTM6MTcwMzk2NTA5M19WNA)
>
> **输入：**intersectVal = 2, listA = [0,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1 **输出：**Intersected at '2' **解释：**相交节点的值为 2 （注意，如果两个链表相交则不能为 0）。 从各自的表头开始算起，链表 A 为 [0,9,1,2,4]，链表 B 为 [3,2,4]。 在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。
>
> **示例 3：**
>
> ![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=M2Q0ODQxODEwMGI2MmQ2OTI2YzEzZTJmZmE0Mjk1OGFfNGY4c3YxeEhUUmdIaTBWWWdvSk9lYmdFZWI4R3VwWElfVG9rZW46WkZXaWJuTnI5b2pDTFV4c2VsVWNoZDlLbndkXzE3MDM5NjE0OTM6MTcwMzk2NTA5M19WNA)
>
> **输入：**intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2 **输出：**null **解释：**从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。 由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。 这两个链表不相交，因此返回 null 。

### 思路

通过示例一发现，两链表相交于某一节点并非是简单的两个节点的值相等，而是两个子链表相等，如果是值相等的话，示例一中的A和B应该相交于节点1。既然如此，那么相交部分的长度肯定相同，结合上一题的思路，先算出两个链表各自的长度，再让较长的链表“先走”

$$\left | lenA - lenB \right | $$

然后注意进行“链表”的比较，如果相等则返回任意链表，不相等的话均往后移动。如果没有相交就返回NULL。

### 代码

```C++
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode * dummyA = new ListNode();
        ListNode * dummyB = new ListNode();
        dummyA -> next = headA;
        dummyB -> next = headB;
        ListNode * curA = dummyA;
        ListNode * curB = dummyB;
        int lenA = 0;
        int lenB = 0;
        while (curA -> next) {
            curA = curA -> next;
            lenA++;
        }
        while (curB -> next) {
            curB = curB -> next;
            lenB++;
        }
        int dif = (lenA - lenB) > 0 ? (lenA - lenB) : (lenB - lenA);
        curA = headA; 
        curB = headB;
        if (lenA > lenB) {
            while (dif--) {
                curA = curA -> next;
            }
        } else {
            while (dif--) {
                curB = curB -> next;
            }
        }
        while (curA  && curB ) {
            if (curA == curB) {
                return curA;
            } else {
                curA = curA -> next;
                curB = curB -> next;
            }
        }
        return NULL;
    }
};
```

### 时空复杂度

时间复杂度：遍历了两个链表，记较长的链表长度为n，较短链表长度为m，在比较过程中最坏情况又遍历了一次较短链表。时间复杂度为O(n+m).

空间复杂度：新建了几个ListNode节点，所以空间复杂度为O(1).

### 学习与小结

1. 此题的虚拟头节点可以不设置，lenA和lenB无需是链表的真实长度，重点是算出长度之差，先让较长的链表和较短的链表“对齐”。
2. 可以使用swap函数将A与B交换，始终保持A为较长（或较短）的链表，能减少代码量。
3. 在最后的比较部分，因为A和B同步移动，所以判断时只需要保证一个链表不为空即可。

## 142. 环形链表 II

### 题目

给定一个链表的头节点  `head` ，返回链表开始入环的第一个节点。 *如果链表无环，则返回* null。

如果链表中有某个节点，可以通过连续跟踪 `next` 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 `pos` 来表示链表尾连接到链表中的位置（**索引从 0 开始**）。如果 `pos` 是 `-1`，则在该链表中没有环。**注意：**`pos`不作为参数进行传递**，仅仅是为了标识链表的实际情况。

**不允许修改** 链表。

> **示例 1：**
>
> **输入：head = [3,2,0,-4],** **pos** **= 1** 
>
> **输出：返回索引为 1 的链表节点**
>
> **解释：链表中有一个环，其尾部连接到第二个节点。**
>
> **示例 2：**
>
> **输入：head = [1,2],** **pos** **= 0** 
>
> **输出：返回索引为 0 的链表节点**
>
> **解释：链表中有一个环，其尾部连接到第一个节点。**
>
> **示例 3：**
>
> **输入：head = [1],** **pos** **= -1** 
>
> **输出：返回** **null** 
>
> **解释：链表中没有环。**

### 思路

外因着急出门/喝了点酒，内因自己菜的不行，没有思路，看了视频讲解后茅塞顿开，因为远古之前做过这个题，所以跟着视频讲解理解起来还是比较易懂的。

这道题首先要判断链表是否有环，如果有环的话要找的环的入口在哪。

又忘记了**双指针**的应用！收回上一道题对于双指针的夸奖，这道题才是双指针最经典的应用。设置快慢指针，快指针相对慢指针每次多走一步，但两个指针均在链表上移动，如果两个指针相遇了，则说明必定有环；如果没有相遇，说明链表无环。而且有环的情况一定是在环内相遇的，因为只要有环，快指针走得快，就在环内一直转圈等待慢指针与他相遇。

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=Y2VmYjJhNzc4NzAzMTZmYWViNTAwMTYwMjU1ZDVlNjNfSFdXeGc1TkpwSXRTVjJiRzVaMElWZkxvTEc3VUJGd0xfVG9rZW46TlI0SWJIWVRDbzJEazh4QXZrbWM5TW9CblhjXzE3MDM5NjE0OTM6MTcwMzk2NTA5M19WNA)

那么如何找到环的入口呢？我们可以用快慢指针走过的路程来计算。假设快指针每次走两步，慢指针每次走一步，且各段的距离如下图所示：

![img](https://pkdwxagc9o.feishu.cn/space/api/box/stream/download/asynccode/?code=ZWMzNGMyZTJjNjRmYWQ1MDY1YjBlZTdkYzZkMDI1NTVfaGIzQXhzV3hqcGlPRTRXeHZkZnQ5c1NZRWRvUFE1bXFfVG9rZW46T2tBMWJ2MzE0b1Zpc1J4U29DUGNjeDhvblpYXzE3MDM5NjE0OTM6MTcwMzk2NTA5M19WNA)

在相遇时，慢指针走过的路程是：x+y；快指针走过的路程是：x+y+n(y+z)，其中m>n；因为路程=时间*速度，所以路程和速度成正比，所以我们可以得到：

$$2(x+y) = x+y+n(y+z) $$

化简有：

$$x+y = n(y+z)$$

进一步处理：

$$x = (n-1)(y+z) + z$$

其中，n>=1.

公式说明快指针多走n圈与慢指针相遇，当n = 1时，x = z，这又说明：从相遇点出发一个指针meet，同一时刻从起点出发一个指针start，当meet走z时，start刚好走x，刚好到环的入口。

当n > 1时，fast在环形转n圈之后才遇到 slow指针。其实这种情况和n为1的时候效果是一样的，一样可以通过这个方法找到环形的入口节点，只不过，meet指针在环里多转了(n-1)圈，然后再遇到start，相遇点依然是环形的入口节点。

理解起来还是 n = 1 时好理解，但是n > 1时也是有实际意义的。

### 代码

```C++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode * slow = head;
        ListNode * fast = head;
        while (fast && fast -> next) {
            slow = slow -> next;
            fast = fast -> next -> next;
            if (slow == fast) {
                ListNode * meet = fast;
                ListNode * start = head;
                while (meet != start) {
                    meet = meet -> next;
                    start = start -> next;
                }
                return meet;
            }
        } 
        return NULL;
    }
};
```

### 时空复杂度

时间复杂度：快慢指针相遇前，指针走的次数小于链表长度，快慢指针相遇后，两个index指针走的次数也小于链表长度，总体为走的次数小于 2n，时间复杂度为O(n).

空间复杂度：新建了几个ListNode节点，所以空间复杂度为O(1).

### 学习与小结

没有思路时一筹莫展，看到讲解茅塞顿开。知识还是没有真正进入到脑子，要多刷多练，将方法形成思想，看到题就能想到对应的方法。对于链表和数组的题，感觉双指针法的应用场景非常的多，所以在没有寻常思路时可以尝试以下双指针法，包括但不限于快指针先走n步，快指针每次比慢指针多走k步，两个指针从两边向中间逼近等等。日后新的双指针法再来补充。