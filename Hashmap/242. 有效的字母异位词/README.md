哈希表

建俩哈希表比一哈？

暴力解法就两层循环，复杂度n方。

数组可以看作是一个哈希表，record[26]这种解法还是很好想到的，但是关键在于key value对应起来，如何把字符与下表映射是个问题。

又学到了  record[s[i] - 'a']++; 

不需要记住字符的阿斯克码，字符与字符的减法可以得到数组的下表，这样就建立起了映射。

也不用建两个数组，只需要遍历第一个时++，遍历第二个时--，最后在看是不是全是0就行了