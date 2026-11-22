bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int m = matrixSize;
    int n = matrixColSize[0];

    int low = 0;
    int high = m * n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        int row = mid / n;
        int col = mid % n;

        if (matrix[row][col] == target) {
            return true;
        }
        else if (matrix[row][col] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return false;

}