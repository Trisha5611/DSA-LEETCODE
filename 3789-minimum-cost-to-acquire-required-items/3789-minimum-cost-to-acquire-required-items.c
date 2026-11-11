long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
    long long option1 = (long long)need1 * cost1
                      + (long long)need2 * cost2;

    int common = (need1 < need2) ? need1 : need2;

    long long option2 = (long long)common * costBoth
                      + (long long)(need1 - common) * cost1
                      + (long long)(need2 - common) * cost2;

    int maximum = (need1 > need2) ? need1 : need2;

    long long option3 = (long long)maximum * costBoth;

    long long ans = option1;

    if (option2 < ans)
        ans = option2;

    if (option3 < ans)
        ans = option3;

    return ans;
}