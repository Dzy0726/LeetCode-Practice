没有很难的算法，主要是模拟的过程。

一开始想实现一个add函数用于模拟循环1/4圈的过程，设置了很多参数，比如起始位置、终止位置、列增加行固定值等，很复杂，没有一个统一标准。

后面看到代码随想录的解法：核心是和二分法一样，确定边界，是左闭右开还是全闭，这样的方便控制每一圈的始末位置。

还要进行一个奇偶判断，补全中间的值。

四个方向即左到右，上到下，右到左，下到上是不能统一的，单独写就好。

看leetcode题解看到一个很简洁的代码，放在下面：

```java
class Solution {
    public int[][] generateMatrix(int n) {
        int l = 0, r = n - 1, t = 0, b = n - 1;
        int[][] mat = new int[n][n];
        int num = 1, tar = n * n;
        while(num <= tar){
            for(int i = l; i <= r; i++) mat[t][i] = num++; // left to right.
            t++;
            for(int i = t; i <= b; i++) mat[i][r] = num++; // top to bottom.
            r--;
            for(int i = r; i >= l; i--) mat[b][i] = num++; // right to left.
            b--;
            for(int i = b; i >= t; i--) mat[i][l] = num++; // bottom to top.
            l++;
        }
        return mat;
    }
}
```

