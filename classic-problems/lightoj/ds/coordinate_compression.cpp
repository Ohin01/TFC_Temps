#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Compression //0-based
{
    vector<ll> vals;

    void build(const vector<ll>& a) 
    {
        vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }

    int get(ll x) 
    {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin(); //+ 1;
    }

    ll rev(int i) 
    {
        return vals[i]; //vals[i - 1];
    }

    // compress entire array
    vector<int> compress_array(const vector<ll>& a) 
    {
        vector<int> res(a.size());

        for (int i = 0; i < a.size(); i++) 
        {
            res[i] = get(a[i]);
        }
        return res;
    }

    pair<int,int> get_range(ll l, ll r) 
    {
        int L = lower_bound(vals.begin(), vals.end(), l) - vals.begin(); // + 1;
        int R = upper_bound(vals.begin(), vals.end(), r) - vals.begin() - 1; // remove -1;

        if (L > R) return {-1, -1}; // no valid range
        return {L, R};
    }
};

void solve()
{
    
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