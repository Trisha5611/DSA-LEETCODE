int countServers(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];

    int row[m], col[n];

    for (int i = 0; i < m; i++)
        row[i] = 0;

    for (int j = 0; j < n; j++)
        col[j] = 0;

    // Count servers in each row and column
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                row[i]++;
                col[j]++;
            }
        }
    }

    int count = 0;

    // Count communicating servers
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1 &&
                (row[i] > 1 || col[j] > 1)) {
                count++;
            }
        }
    }

    return count;
}