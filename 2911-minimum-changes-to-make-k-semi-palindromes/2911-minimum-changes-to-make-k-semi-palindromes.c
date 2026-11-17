#define INF 1000000
int minimumChanges(char* s, int k) {
  int n = strlen(s);

int cost[200][200];


for (int l = 0; l < n; l++) {
    for (int r = l + 1; r < n; r++) {

        int len = r - l + 1;
        cost[l][r] = INF;

       
        for (int d = 1; d < len; d++) {

            if (len % d != 0)
                continue;

            int changes = 0;

            
            for (int offset = 0; offset < d; offset++) {

                int count = (len - 1 - offset) / d + 1;

                
                for (int t = 0; t < count / 2; t++) {

                    int i = l + offset + t * d;
                    int j = l + offset + (count - 1 - t) * d;

                    if (s[i] != s[j])
                        changes++;
                }
            }

            if (changes < cost[l][r])
                cost[l][r] = changes;
        }
    }
}

// Step 2: Dynamic Programming
int dp[101][201];

for (int i = 0; i <= k; i++) {
    for (int j = 0; j <= n; j++) {
        dp[i][j] = INF;
    }
}

dp[0][0] = 0;

for (int parts = 1; parts <= k; parts++) {

    for (int end = 2 * parts; end <= n; end++) {

        for (int start = 2 * (parts - 1);
             start <= end - 2; start++) {

            if (dp[parts - 1][start] == INF)
                continue;

            int current = dp[parts - 1][start]
                        + cost[start][end - 1];

            if (current < dp[parts][end])
                dp[parts][end] = current;
        }
    }
}

return dp[k][n];  
}