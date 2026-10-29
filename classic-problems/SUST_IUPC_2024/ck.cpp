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
    if(rep == "Yes") {
        int k; 
        assert(cin>>k);
        while(k--) {
            int l, r; cin>>l>>r; --l, --r;

            for(int j=l; j<=r; ++j) rem[j] = false;

            int curvol = 0, curwater = 0;
            for(int j=l; j<=r; ++j) {
                curvol += vol[j];
                curwater += water[j];
            }

            if(bad(curvol, curwater)) ++b;
            else ++g;
        }

        for(int i=0; i<n; ++i) if(rem[i]) {
            if(bad(vol[i], water[i])) ++b;
            else ++g;
        }

        assert(g > b);
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