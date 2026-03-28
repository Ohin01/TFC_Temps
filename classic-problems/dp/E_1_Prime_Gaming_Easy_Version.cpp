#include<bits/stdc++.h>
using namespace std;

#define pb              push_back
#define ff              first
#define ss              second
#define index           find_by_order
#define FOR(i, a, b)    for(int i = (a); i < (b); i++)
#define FORR(i, a, b)    for(int i = (a); i >= (b); i--)
#define YES             cout << "YES\n"
#define NO              cout << "NO\n"
#define lcm(a, b)       ((a / __gcd(a, b)) * b)
 

int dp[20][(1<<20)][2];
int n;

int shift(int num, int ind, int limit)
{
    int f = ind;
    int s = ind + 1;

    int ans = 0;

    FOR(i, 0, f)
    {
        if ((num & (1<<i)) == 0) continue;
        else ans += (1<<i);
    }

    while (s < limit + 1)
    {
        if ((num & (1<<s)) != 0) ans += (1<<(s - 1));
        s++;
    }

    return ans;
}

int shift_fast(int mask, int ind) {
    int low = mask & ((1LL << ind) - 1);
    int high = mask >> (ind + 1);
    return low | (high << ind);
}


void solve()
{
    cin >> n;

    int m;
    cin >> m;

    int k;
    cin >> k;

    FOR(i, 0, n + 1)
    {
        FOR(j, 0, (1<<(n)))
        {
            FOR(l, 0, 2)
            dp[i][j][l] = 0;
        }
    }

    vector<int> c(k);
    
    FOR(i, 0, k) cin >> c[i];

    FOR(i, 0, k) c[i]--;

    if (m == 1) 
    {
        cout << 1 << endl;
        return;
    }

    dp[0][0][0] = 1;
    dp[0][1][0] = 2;
    
    dp[0][0][1] = 1;
    dp[0][1][1] = 2;

    FOR(i, 1, n)
    {
        FOR(j, 0, (1<<(i + 1)))
        {
            FOR(turn, 0, 2)
            {
                int ans;
                if (turn == 0) ans = 1;
                else ans = 2;

                for (auto l: c)
                {
                    if (l > i) break;

                    if (turn == 0 && dp[i - 1][shift_fast(j, l)][turn ^ 1] == 2)
                    {
                        ans = 2;
                        break;
                    }

                    else if (turn == 1 && dp[i - 1][shift_fast(j, l)][turn ^ 1] == 1)
                    {
                        ans = 1;
                        break;
                    }
                }

                dp[i][j][turn] = ans;

                //cout << i << " " << j << " " << turn << " " << dp[i][j][turn] << endl;
            }
        }
    }

    int ans = 0;

    FOR(i, 0, (1<<n))
    {
        //cout << dp[n - 1][i][0] << endl;
        ans += dp[n - 1][i][0];
    }

    cout << ans << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    while (cases--)
    {
        solve();
    }
}