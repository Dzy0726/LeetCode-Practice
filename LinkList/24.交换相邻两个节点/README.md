emm又忘了加虚拟头节点，主要是虚拟头节点方便方便返回，不然每次要单独处理头结点。

感觉写链表循环不必先判断出循环终止的条件，应该先搞清楚循环内部的流程，内部流程跑的通，终止条件自然就出来了。这道题要跨两位，如果按照平常的循环终止条件就行不通，所以要先模拟完循环内部交换的步骤，再得到终止条件。



看了其他的解法，发现一个不错的思路，虽然这道题不一定好用

栈是方便这种逆序或者交换的，两次进栈两次出栈刚好交换两个的前后顺序

