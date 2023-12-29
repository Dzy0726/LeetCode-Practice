# **代码随想录算法训练营第三天| 链表 Part01**

- 203.[移除链表元素](https://leetcode.cn/problems/remove-linked-list-elements/) 
- 707.[设计链表](https://leetcode.cn/problems/design-linked-list/)
- 206.[反转链表](https://leetcode.cn/problems/reverse-linked-list/) 

## LeetCode 203. 移除链表元素

给你一个链表的头节点 `head` 和一个整数 `val` ，请你删除链表中所有满足 `Node.val == val` 的节点，并返回 **新的头节点** 。

**示例 1：**

```
输入：head = [1,2,6,3,4,5,6], val = 6
输出：[1,2,3,4,5]
```

**示例 2：**

```
输入：head = [], val = 1
输出：[]
```

**示例 3：**

```
输入：head = [7,7,7,7], val = 7
输出：[]
```

### 思路

思路比较简单，遍历链表依次寻找值等于val的节点，若找到则删除，直到链表遍历结束。在这里使用了虚拟头节点dummy，指向题中所给的真实头节点head，这样就不用单独讨论head的值为val的情况。current指向当前遍历的位置，tmp指向即将要被检查（删除）的节点。

### 代码

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode * dummy = new ListNode();
        dummy->next = head;
        ListNode * current = new ListNode();
        ListNode * tmp = new ListNode();
        current = dummy;
        while (current->next) {
            tmp = current->next;
            if (tmp->val == val) {
                current->next = tmp->next;
            } else {
                current = tmp;
            }
        }
        return dummy->next;
    }
};
```

### 时空复杂度

- 时间复杂度：循环过程中每个节点遍历了一次，时间复杂度为O(n).
- 空间复杂度：新建了几个ListNode节点，所以空间复杂度为O(1).

### 学习与小结

- 首先是C++动态申请内存：`ListNode * dummy = new ListNode()`;
- C++手动释放：`delete dummy`;
- 为什么要用虚拟头节点：使删除操作统一，不然得单独处理头节点就是要删的节点的情况；
- 为什么要用current甚至tmp：删除链表节点需要有该链表节点的前驱，如果tmp是要删除的节点，则current就需要当他的前驱。而循环中dummy是不动的，dummy->next始终指向要返回的节点，所以需要current来遍历。current是必须的，tmp不是必须的，也可以`cur->next = cur->next->next`.
- 跳出while循环的条件：只要current->next不空即可，保证能取到下一个值。删除最后一个节点，只要最后一个节点不为空（倒数第二个节点->next不为空），即可删除后让倒数第二个节点的next指向NULL，也符合跳出循环的条件。



## LeetCode 707.设计链表

你可以选择使用单链表或者双链表，设计并实现自己的链表。

单链表中的节点应该具备两个属性：`val` 和 `next` 。`val` 是当前节点的值，`next` 是指向下一个节点的指针/引用。

如果是双向链表，则还需要属性 `prev` 以指示链表中的上一个节点。假设链表中的所有节点下标从 **0** 开始。

实现 `MyLinkedList` 类：

- `MyLinkedList()` 初始化 `MyLinkedList` 对象。
- `int get(int index)` 获取链表中下标为 `index` 的节点的值。如果下标无效，则返回 `-1` 。
- `void addAtHead(int val)` 将一个值为 `val` 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点。
- `void addAtTail(int val)` 将一个值为 `val` 的节点追加到链表中作为链表的最后一个元素。
- `void addAtIndex(int index, int val)` 将一个值为 `val` 的节点插入到链表中下标为 `index` 的节点之前。如果 `index` 等于链表的长度，那么该节点会被追加到链表的末尾。如果 `index` 比长度更大，该节点将 **不会插入** 到链表中。
- `void deleteAtIndex(int index)` 如果下标有效，则删除链表中下标为 `index` 的节点。

**示例 ：**

```
输入
["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
[[], [1], [3], [1, 2], [1], [1], [1]]
输出
[null, null, null, null, 2, null, 3]

解释
MyLinkedList myLinkedList = new MyLinkedList();
myLinkedList.addAtHead(1);
myLinkedList.addAtTail(3);
myLinkedList.addAtIndex(1, 2);    // 链表变为 1->2->3
myLinkedList.get(1);              // 返回 2
myLinkedList.deleteAtIndex(1);    // 现在，链表变为 1->3
myLinkedList.get(1);              // 返回 3
```

### 思路

链表的创建、增加、删除、查找等操作的实现，太久不写代码，类的相关知识已经忘记了，包括公有变量、私有变量等知识。

初始化`MyLinkedList`：之前203题提到了使用虚拟头节点的好处，在这里仍然使用虚拟头节点，但是虚拟头节点并不计入链表的长度。因为后面操作涉及到指定位置的插入和删除，所以有一个size私有变量记录当前链表长度便于后续操作。

取值`int get(int index)` ：index合法就是小于链表长度，因为下表从0开始，所以下标的最大值是链表长度减一。

头插`void addAtHead(int val)`：由于虚拟头节点的存在，头插和在其余位置插入统一，甚至更简单。

尾插`void addAtTail(int val)`：用current指向当前节点，只要下一个节点不空就一直往后移动，如果current->next为空，说明到了链表末尾，在这里插入即可。

任意位置插入`void addAtIndex(int index, int val)`：先判断index是否合法，index大于链表长度则不插入新节点；index等于链表长度则插入到末尾，直接使用尾插函数；index小于链表长度，index--直到找到应该插入位置的**前驱节点**，然后进行插入。

任意位置删除`void deleteAtIndex(int index)`：先判断index是否合法，合法的话和插入类似，找到要删除节点的前驱节点，再进行删除。

要注意在插入后要使链表长度加一，删除后要使链表长度减一。

### 代码

```c++
class MyLinkedList {
public:
    struct ListNode {
        int val;
        ListNode * next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int val): val(val), next(nullptr) {}
    };

    MyLinkedList() {
        _dummy = new ListNode();
        _size = 0;
    }
    
    int get(int index) {
        if (index >= _size) {
            return -1;
        }
        ListNode * current = _dummy;
        while (index--) {
            current = current->next;
        }
        return current->next->val;
    }
    
    void addAtHead(int val) {
        ListNode * newNode = new ListNode(val);
        newNode->next = _dummy->next;
        _dummy->next = newNode;
        _size++;
        showLink();
    }
    
    void addAtTail(int val) {
        ListNode * current = _dummy;
        ListNode * newNode = new ListNode(val);
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
        _size++;
    }
    
    void addAtIndex(int index, int val) {
        ListNode * newNode = new ListNode(val);
        ListNode * current = _dummy;
        if (index > _size) {
            return;
        }
        if (index == _size ) {
            addAtTail(val);
            return;
        }
        while (index--) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        _size++;
    }
    
    void deleteAtIndex(int index) {
        if (index >= _size) {
            return;
        }
        ListNode * current = _dummy;
        while (index--) {
            current = current->next;
        }
        current->next = current->next->next;
        _size--;
    }

private:        
    int _size;
    ListNode* _dummy;
};
```

### 时空复杂度

- 时间复杂度：涉及 `index` 的相关操作为 O(index), 其余为 O(1).
- 空间复杂度：O(n)

### 学习与小结

1. 链表是由一个个链表节点构成的，所以在定义链表的构造函数之前，还需要定义链表节点的结构体。要熟悉结构体的定义方法和构造函数的定义方法：

   ```C++
   struct LinkedNode {
       int val;
       LinkedNode * next;
       LinkedNode() : val(0), next(nullptr){}
       LinkedNode(int val): val(val), next(nullptr){}
       LinkedNode(int val, LinkedNode * next): val(val), next(next){}
   };
   ```

2. 私有变量：\_dummy便于统一操作，\_size便于检查index是否合法。外部不能访问，只有在类内可以访问。

3. 链表构造函数：就是对链表进行一个初始化，设置虚拟头节点、链表初始长度为0。

4. index的非法判断：除了index大于链表长度之外，还要看index是否小于0.

5. delete：delete命令只是释放了该指针原本所指的那部分内存，而他的值（一个地址）并不是NULL，而是随机值。也就是delete之后需要加上`tmp=nullptr`，否则tmp就会变成野指针。



## LeetCode 206. 反转链表

### 题目

给你单链表的头节点 `head` ，请你反转链表，并返回反转后的链表。

**示例 1：**

```
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
```

**示例 2：**

```
输入：head = [1,2]
输出：[2,1]
```

### 思路

和昨天的滑动窗口一样，八个月前做过但是还是忘记了……一直想着把尾部节点加入后就删掉，循环直到head为空。这种思路不仅复杂，还非常容易出错，访问到空指针。而且再定义一个链表也会造成内存空间的浪费。

要把链表的头前面看做一个空节点，这样才能用一套反转逻辑，不然初始状态的head->next还是指向下一个

比如链表：1-2-3-4-5

初始链表其实是：1-2-3-4-5-NULL

反转以后应该是5-4-3-2-1-NULL

所以就把他看成 NULL-1-2-3-4-5

这样处理的话pre初始就是null，cur初始为head，tmp接cur的后一个，就可以用一套逻辑处理。

### 代码

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode * pre = nullptr;
        ListNode * cur = head;
        while (cur) {
            ListNode * tmp = cur -> next;
            cur -> next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
};
```

### 时空复杂度

- 时间复杂度：遍历了一次链表，O(n).
- 空间复杂度：几个链表节点，空间复杂度O(1).

### 学习与小结

这个题画图画了很久，比起之前做，进步在有意识的去用多个指针，尽可能统一的用一套处理方法。但是在画图时出现了纰漏，`cur->next=pre`之后，箭头就应该即时删掉，否则就多了一步操作，导致错误。

反转链表不能一上来就想着从后往前一步到位，可以画图试着把箭头一个个反转过来，而不是一整个链表一下子翻转过来。



