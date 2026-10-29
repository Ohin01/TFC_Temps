    #include <bits/stdc++.h>
    using namespace std;


    void solve() {
        int n; cin>>n;
        vector<string>g(n);

        for(string &s : g) cin>>s;

        string ans;

        for(string s : g) {
            int m = s.size();
            for(int i=1; i<m; ++i) {
                if(s[i] >= 'A' && s[i] <= 'Z') s[i] = (s[i] - 'A') + 'a';
            }
            if(s[0] >= 'a' && s[0] <= 'z') s[0] = (s[0] - 'a') + 'A';


            ans += s;
        }

        cout<<ans<<"\n";
    }

    int main() {
        ios_base::sync_with_stdio(0);
        cin.tie(0);

        int t = 1;
        while(t--) {
            solve();
        }
        return 0;
    }