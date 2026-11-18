char* multiply(char* num1, char* num2) {
    int n = strlen(num1);
int m = strlen(num2);

int* result = calloc(n + m, sizeof(int));

for (int i = n - 1; i >= 0; i--) {

    for (int j = m - 1; j >= 0; j--) {

        int mul = (num1[i] - '0') * (num2[j] - '0');

        int sum = mul + result[i + j + 1];

        result[i + j + 1] = sum % 10;

        result[i + j] += sum / 10;
    }
}

char* ans = malloc((n + m + 1) * sizeof(char));

int k = 0;
int i = 0;

while (i < n + m && result[i] == 0)
    i++;

if (i == n + m) {
    ans[k++] = '0';
}
else {
    while (i < n + m) {
        ans[k++] = result[i] + '0';
        i++;
    }
}

ans[k] = '\0';

free(result);

return ans;
}