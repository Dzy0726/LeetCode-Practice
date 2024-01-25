class Solution {
public:
    vector<vector<string>> result;
    void backtracking(int n, int row, vector<string>& chessBoard) {
        if (row == n) {
            result.push_back(chessBoard);
            return;
        }
        for (int col = 0; col < n; col++) {
            if (isValid(row, col, n, chessBoard)) {
                chessBoard[row][col] = 'Q';
                backtracking(n, row + 1, chessBoard);
                chessBoard[row][col] = '.';
            }
        }
    }
    bool isValid(int row, int col, int n,vector<string> chessBoard) {
        for (int i = 0; i < row; i++) {
            if (chessBoard[i][col] == 'Q') return false;
        }
        for (int i = row - 1, j = col - 1; i >= 0 && j >=0; i--, j--) {
            if (chessBoard[i][j] == 'Q') return false;
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (chessBoard[i][j] == 'Q') return false;
        }
        return true;
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<string> chessBoard(n, string(n, '.'));
        backtracking(n, 0, chessBoard);
        return result;
    }
};