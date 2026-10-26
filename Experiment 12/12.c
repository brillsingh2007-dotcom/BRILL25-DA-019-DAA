```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void matrixChainMultiplication(vector<int>& p, int n) {
    vector<vector<long long>> dp(
        n, vector<long long>(n, 0)
    );

    // L is the chain length
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long cost = dp[i][k]
                    + dp[k + 1][j]
                    + 1LL * p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    cout << "\nMinimum number of scalar multiplications: "
         << dp[1][n - 1] << endl;
}

int main() {
    int n;

    cout << "Enter the number of matrices: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of matrices!" << endl;
        return 1;
    }

    vector<int> p(n + 1);

    cout << "Enter the dimensions array ("
         << n + 1 << " integers):\n";

    for (int i = 0; i <= n; i++) {
        cin >> p[i];

        if (p[i] <= 0) {
            cout << "Dimensions must be positive!" << endl;
            return 1;
        }
    }

    matrixChainMultiplication(p, n + 1);

    return 0;
}
```
