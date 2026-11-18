bool dfs(char** board, int r, int c, int m, int n, char* word, int index) {

if (word[index] == '\0')
    return true;

if (r < 0 || c < 0 || r >= m || c >= n)
    return false;

if (board[r][c] != word[index])
    return false;

char temp = board[r][c];
board[r][c] = '#';

bool found = dfs(board, r + 1, c, m, n, word, index + 1) ||
             dfs(board, r - 1, c, m, n, word, index + 1) ||
             dfs(board, r, c + 1, m, n, word, index + 1) ||
             dfs(board, r, c - 1, m, n, word, index + 1);

board[r][c] = temp;

return found;

}
bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    int m = boardSize;
int n = boardColSize[0];

for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {

        if (board[i][j] == word[0]) {
            if (dfs(board, i, j, m, n, word, 0))
                return true;
        }
    }
}

return false;
}