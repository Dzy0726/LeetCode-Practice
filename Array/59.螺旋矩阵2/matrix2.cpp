class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int> (n));
        int count = 1; //递增元素
        int loop = n / 2; 
        int mid = n / 2;
        int start = 0;
        int offset = 1; //meiquan kongjigezhi
        int i, j;
        while(loop--) {
            for(j = start; j < n - offset; j++) {
                matrix[start][j] = count++;
            }
            for(i = start; i < n - offset; i++) {
                matrix[i][j] = count++;
            }
            for(; j > start; j--) {
                matrix[i][j] = count++;
            }
            for(; i > start; i--) {
                matrix[i][j] = count++;
            }
            offset++;
            start++;
        }
        if(n % 2) {
            matrix[mid][mid] = count;
        }
        return matrix;
    }
};