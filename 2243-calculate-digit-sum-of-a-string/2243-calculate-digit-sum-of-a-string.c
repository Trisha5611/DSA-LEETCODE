char* digitSum(char* s, int k) {
    while (strlen(s) > k) {
        char temp[200] = "";
        int len = strlen(s);

        for (int i = 0; i < len; i += k) {
            int sum = 0;

            for (int j = i; j < i + k && j < len; j++) {
                sum += s[j] - '0';
            }

            char num[10];
            sprintf(num, "%d", sum);
            strcat(temp, num);
        }

        strcpy(s, temp);
    }

    return s;
}