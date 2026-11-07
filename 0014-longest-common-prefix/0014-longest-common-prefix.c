char* longestCommonPrefix(char** strs, int strsSize) {
     static char result[201];

    int i, j;

    // Compare characters of the first string
    for (i = 0; strs[0][i] != '\0'; i++) {

        char ch = strs[0][i];

        // Check this character in all other strings
        for (j = 1; j < strsSize; j++) {

            if (strs[j][i] != ch) {
                result[i] = '\0';
                return result;
            }
        }

        result[i] = ch;
    }

    result[i] = '\0';

    return result;
}