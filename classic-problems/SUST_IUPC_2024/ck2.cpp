#include <bits/stdc++.h>
using namespace std;

bool bad(long long vol, long long con) {
    return con * 2 <= vol;
}
void solve() {
    int n; cin>>n;

    int vol[n];
    for(int i=0; i<n; ++i) cin>>vol[i];
    int water[n];
    for(int i=0; i<n; ++i) cin>>water[i];

    string rep; cin>>rep;

    bool rem[n];
    for(int i=0; i<n; ++i) rem[i] = 1;


    int b = 0, g = 0;
    if(rep == "No") {
        vector<int>dp(n+1, 0);

        for(int i=n-1; i>=0; --i) {

            dp[i] = -n;

            long long curvol = 0, curwater = 0;
            for(int j=i; j<n; ++j) {
                curvol += vol[j];
                curwater += water[j];

                dp[i] = max(dp[i], dp[j+1] + (bad(curvol, curwater) ? -1 : 1));
            }
        }

        if(dp[0] > 0) assert(false);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while(t--) {
        solve();
    }
    return 0;
}