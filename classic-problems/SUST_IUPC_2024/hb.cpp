#include <bits/stdc++.h>
using namespace std;


void solve() {
    int n; cin>>n;
    long long a[n];
    
    for(int i=0; i<n; ++i) cin>>a[i];

    long long ans = -1e18;

    for(int i=0; i<n; ++i) {
        for(int j=i; j<n; ++j) {
            long long sum = 0, mx = -1e18;

            for(int k=i; k<=j; ++k) {
                sum += a[k];
                mx = max(mx, a[k]);
            }

            ans = max(ans, mx * sum);
        }
    }

    cout<<ans<<"\n";
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