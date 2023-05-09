这道题也算是秒了，终于可以秒一道题了

思路和之前做过的一道字母的题类似，一个26长度的数组，先记录magazine中每个字符出现的次数，再依次判断够不够ransomNote的每个字符用，不够直接return false 。

标准解法的思路也是这样，但是多了一步判断

```cpp
 if (ransomNote.size() > magazine.size()) {
            return false;
        }
```
b包含a，但a比b长直接判断
这种细节也是要注意的！
