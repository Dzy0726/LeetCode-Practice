移除链表元素，易混淆的点在于head、current、temp等等的代替

个人感觉虚拟一个头节点处理起来很方便

增加一个虚拟头节点：

vir->next = head

用cur来操作删除：

cur = vir

循环的时候也是用cur来循环

while(cur->next)

只要下一个不空 就判断下一个值是不是目标值，如果是，则new一个tmp=next，然后cur的next等于tmp的next（相当于自己的next的next），然后delete tmp；如果不等于目标值，则往后推一个继续循环。

C++需要手动释放内存，python和java不需要