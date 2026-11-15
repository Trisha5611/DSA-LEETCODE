int longestValidParentheses(char* s) {
    int n = strlen(s);
    int stack[n + 1];
    int top = -1;
    int maxLen = 0;

    stack[++top] = -1;

    for (int i = 0; i < n; i++) {

        if (s[i] == '(') {
            stack[++top] = i;
        }
        else {
            top--;

            if (top == -1) {
                stack[++top] = i;
            }
            else {
                int len = i - stack[top];

                if (len > maxLen) {
                    maxLen = len;
                }
            }
        }
    }

    return maxLen;
}