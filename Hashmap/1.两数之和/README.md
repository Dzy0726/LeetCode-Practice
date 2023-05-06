先两层循环暴力体验一下秒的感觉~

注意：

- 元素不能重复利用，所以循环时要j=i+1开始
- 找到了就要及时跳出循环





想到用map 但是key value没搞对

我想的是key为一个pair<int,int> 存答案，value是sum，然后和target匹配

但这样仍然要遍历，复杂度没降下来



正确解法应该是key存nums元素的值，value存下标，遍历的时候找map中是否存在一个target-nums[i]，即map中是否存在一个数和当前的nums[i]凑成target，如果有就返回他们的下标，并break；没有就把当前的数组元素加入map。



一些操作方法：

map.insert()：map的插入要差一个键值对，可以这样写pair<int,int>(i,j)

map.find() 找到的话返回的是迭代器，没找到返回的是map.end()这个迭代器

map取value，先找到该迭代器it，然后it->second取值

