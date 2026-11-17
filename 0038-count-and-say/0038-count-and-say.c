char* countAndSay(int n) {
   char *current = malloc(10000);
char *next = malloc(10000);

strcpy(current, "1");

for (int i = 1; i < n; i++) {

    int j = 0;
    int k = 0;

    while (current[j] != '\0') {

        char ch = current[j];
        int count = 0;

        // Count consecutive identical digits
        while (current[j] == ch) {
            count++;
            j++;
        }

        // Store count and digit
        k += sprintf(next + k, "%d%c", count, ch);
    }

    next[k] = '\0';

    strcpy(current, next);
}

free(next);

return current; 
}