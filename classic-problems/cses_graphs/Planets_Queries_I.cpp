#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;

#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

const int MAX = 2e5 + 5;

void fillAncestor(int n, vvi &suc)
{
    FOR(i, 1, 30)
    {
        FOR(j, 1, n + 1)
        {
            if (suc[j][i - 1] != -1)
            suc[j][i] = suc[ suc[j][i - 1] ][i - 1];

            else
            suc[j][i] = -1;
        }
    }
}

int kthAncestor(int node, int k, vvi &suc)
{
    int ans = node;

    FOR(i, 0, 30)
    {
        if ((k & (1<<i)) != 0)
        {
            ans = suc[ans][i];

            if (ans == -1) return -1;
        }
    }

    return ans;
}


void solve()
{
    int n;
    cin >> n;

    int q;
    cin >> q;

    vvi suc(n + 1, vi(30, -1));

    FOR(i, 1, n + 1)
    {
        int nn;
        cin >> nn;

        suc[i][0] = nn;
    }

    fillAncestor(n, suc);

    while (q--)
    {
        int u, k;
        cin >> u >> k; 

        cout << kthAncestor(u, k, suc) << "\n";
    }


}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    while (cases--)
    {
        solve();
    }
}