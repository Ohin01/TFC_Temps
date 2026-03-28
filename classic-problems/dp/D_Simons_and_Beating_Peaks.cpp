#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;

#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)


const int N = 5e5 + 9;

int n, tot, st[N], l[N], r[N], vis[N];
pair<int, int> a[N];

int cartesian_tree() {
    tot = 0;
    for (int i = 1; i <= n; i++) l[i] = r[i] = vis[i] = 0;
    for (int i = 1; i <= n; i++) {
        int k = tot;
        while (k > 0 && a[st[k - 1]] < a[i]) k--; //use > for min heap
        if (k) r[st[k - 1]] = i;
        if (k < tot) l[i] = st[k];
        st[k++] = i;
        tot = k;
    }
    for (int i = 1; i <= n; i++) vis[l[i]] = vis[r[i]] = 1;
    int rt = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) rt = i;
    }
    return rt;
}

int dfs(int node)
{
    ll a1 = 0, a2 = 0;
    if (l[node]) a1 = dfs(l[node]);
    if (r[node]) a2 = dfs(r[node]);

    return 1 + max(a1, a2);
}

void solve2()
{
    cin >> n;

    FOR(i, 1, n + 1) 
    {
        int x;
        cin >> x;

        a[i] = {x, -i};
    };

    int root = cartesian_tree();

    cout << n - dfs(root) << endl;
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
        solve2();
    }
}