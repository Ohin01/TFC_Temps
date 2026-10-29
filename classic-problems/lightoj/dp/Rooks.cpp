#include<bits/stdc++.h>
using namespace std;

long long dp[31][31];

int main(void)
{    
    int cases = 1;
    cin >> cases;

    dp[1][1] = 1;
    dp[1][0] = 1;

    for (int i = 2; i < 31; i++)
    {
        for (int j = 0; j < 31; j++)
        {
            if (j > i) break;

            dp[i][j] = dp[i - 1][j];

            if (j - 1 >= 0)
            dp[i][j] += dp[i - 1][j - 1] * ((i * i - (i - 1) * (i - 1)) - 2 * (j - 1));

            if (j - 2 >= 0)
            dp[i][j] += dp[i - 1][j - 2] * ((i - 1) - (j - 2)) * ((i - 1) - (j - 2)); 

            //if (i == 2 && j == 2) cout << ((i * i - (i - 1) * (i - 1)) - 2 * (j - 1)) << " " << i - 1 << " " << j - 2<< " " << ((i - 1) - j - 2) * ((i - 1) - j - 2) << endl;
        }
    }

    // FOR(i, 1, 5)
    // {
    //     FOR(j, 0, 5) cout << dp[i][j] << " ";
    //     cout << endl;
    // }

    for (int i = 1; i <= cases; i++)
    {
        cout << "Case " << i << ": ";
        int n, k;
        cin >> n >> k;

        if (k > n) cout << 0 << endl;
        else cout << dp[n][k] << endl;
    }
}