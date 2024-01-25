class Solution {
public:
    bool backtracking(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    continue;
                }
                for (char k = '1'; k <= '9'; k++) {
                    if (isValid(k, i, j, board)) {
                        board[i][j] = k;
                        if (backtracking(board)) return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }

    bool isValid(char n, int row, int col, vector<vector<char>> board) {
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == n) return false;
        }
        for (int i = 0; i < 9;i++) {
            if (board[row][i] == n) return false;
        }
        int startrow = (row / 3) * 3;
        int startcol = (col / 3) * 3;
        for (int i = startrow; i < startrow + 3; i++) {
            for (int j = startcol; j < startcol + 3; j++) {
                if (board[i][j] == n) return false;
            }
        }
        return true;
    }
    void a(vector<vector<char>>& board) {
        backtracking(board);
    }
};