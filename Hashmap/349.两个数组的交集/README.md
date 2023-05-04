这个题一开始想别map或者set了，用数组解决

结果发现数组解决重复元素的时候有点麻烦，还是练一下map的使用

该题要求输出无重复元素，且无序

所以可以考虑unordered map

声明：    unordered_map<int, int> my_map; 

操作value值可以像数组一样：my_map[nums1[i]] = 1;   

使用迭代器访问元素 ：for (const auto &pair : my_unordered_map) {        std::cout << pair.first << ": " << pair.second << std::endl;    }

删除元素：my_unordered_map.erase("orange");

有按key查找，按value的话要遍历一下

