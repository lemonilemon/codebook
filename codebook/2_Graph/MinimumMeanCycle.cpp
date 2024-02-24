
/* O(V^3)
let dp[i][j] = min length from 1 to j exactly i edges
ans = min (dp[n + 1][u] - dp[i][u]) / (n + 1 - i) */
