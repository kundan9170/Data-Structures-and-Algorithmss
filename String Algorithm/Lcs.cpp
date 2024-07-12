// Function to find the LCS of two strings
int lcs(const string &X, const string &Y) {
    int m = X.size();
    int n = Y.size();
    vector<vector<int>> L(m + 1, vector<int>(n + 1));

    // Build the L[m+1][n+1] table in bottom-up fashion
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    // L[m][n] contains the length of LCS for X[0..m-1], Y[0..n-1]
    return L[m][n];
}
