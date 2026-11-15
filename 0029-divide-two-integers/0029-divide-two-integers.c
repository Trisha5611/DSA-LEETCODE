int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1)
        return INT_MAX;

    long long a = dividend;
    long long b = divisor;

    int sign = 1;

    if (a < 0) {
        a = -a;
        sign = -sign;
    }

    if (b < 0) {
        b = -b;
        sign = -sign;
    }

    long long result = 0;

    while (a >= b) {
        long long temp = b;
        long long count = 1;

        while (a >= (temp << 1)) {
            temp <<= 1;
            count <<= 1;
        }

        a -= temp;
        result += count;
    }

    return sign == 1 ? result : -result;
}