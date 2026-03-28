#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef long double     ld;
typedef vector<ll>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;

#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

const ll MAX = 2e5 + 5;

const ll MX = 2e5 + 9; 
ll root[MX];

struct Node
{
    ll left = 0;
    ll right = 0;
    ll val = 0;
};

Node nodes[MX * 25];

struct PerSegTree
{
    ll id = 0;

    ll build(vll &a, ll lx, ll rx)
    {
        ll cur = ++id;

        if (lx == rx)
        {
            nodes[cur].val = a[lx];
            return cur;
        }

        ll mid = (lx + rx) / 2;

        nodes[cur].left = build(a, lx, mid);
        nodes[cur].right = build(a, mid + 1, rx);

        nodes[cur].val = nodes[nodes[cur].left].val + nodes[nodes[cur].right].val;

        return cur;
    }

    ll update(ll prev, ll i, ll v, ll lx, ll rx)
    {
        ll cur = ++id;

        nodes[cur] = nodes[prev];

        if (lx == rx)
        {
            nodes[cur].val += v;
            return cur;
        }

        ll mid = (lx + rx) / 2;

        if (i <= mid) 
        {
            nodes[cur].left = update(nodes[cur].left, i, v, lx, mid);
        }

        else
        {
            nodes[cur].right = update(nodes[cur].right, i, v, mid + 1, rx);
        }

        nodes[cur].val = nodes[nodes[cur].left].val + nodes[nodes[cur].right].val;
        return cur;
    }

    ll getSum(ll cur, ll l, ll r, ll lx, ll rx)
    {
        if (rx < l || r < lx)
        {
            return 0;
        }

        if (lx >= l && rx <= r)
        {
            return nodes[cur].val;
        }

        ll mid = (lx + rx) / 2;

        return getSum(nodes[cur].left, l, r, lx, mid) + getSum(nodes[cur].right, l, r, mid + 1, rx);
    }
};

vector<ll> vals;

void build_compress() {
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
}

ll compress(ll x) {
    return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
}

vvll graph(MAX);
vvll par(MAX, vll(20, 0));

PerSegTree pst;

void dfs(ll node, ll parent)
{
    par[node][0] = parent;

    for (auto child: graph[node])
    {
        if (child == parent) continue; 

        dfs(child, node);
    }
}

void fillAncestor(ll n)
{
    FOR(i, 1, 20)
    {
        FOR(j, 1, n + 1)
        {
            if (par[j][i - 1] != 0)
            par[j][i] = par[ par[j][i - 1] ][i - 1];

            else
            par[j][i] = 0;
        }
    }
}

ll kthAncestor(ll node, ll k)
{
    ll ans = node;

    FOR(i, 0, 20)
    {
        if ((k & (1<<i)) != 0)
        {
            ans = par[ans][i];

            if (ans == 0) return 0;
        }
    }

    return ans;
}

void findRoots(ll node, ll parent, vll &p, vll &k, ll N)
{
    ll val = compress(p[node]);
    root[node] = pst.update(root[parent], val, k[node], 1, N);

    for (auto child: graph[node])
    {
        if (child != parent)
        findRoots(child, node, p, k, N);
    }
    
}




void solve()
{
    ll n;
    cin >> n;

    FOR(i, 0, n - 1)
    {
        ll u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, 0);
    fillAncestor(n);

    vll k(n + 1);
    vll p(n + 1);

    FOR(i, 1, n + 1)
    {
        cin >> k[i];
        cin >> p[i];

        vals.push_back(p[i]);
    }

    build_compress();
    ll N = vals.size();

    vll temp(N + 1, 0);

    root[0] = pst.build(temp, 1, N);
    
    findRoots(1, 0, p, k, N);

    // FOR(i, 1, N + 1)
    // {
    //     //cout << compress(i) << " ";
    //     cout << pst.getSum(root[8], i, i, 1, N) << endl;;
    // }

    ll ans = 0;
    ll MOD = 1e9;

    ll q;
    cin >> q;
    //q = 1;

    //cout << q << endl;

    while (q--)
    {
        ll U, D, PL, PU;
        cin >>U >> D >>PL >> PU;

        ll u = (U + ans) % n + 1;
        ll d = (D + ans) % n;
        ll pl = (PL + ans) % MOD + 1;
        ll pu = (PU + ans) % MOD + 1;

        if (pl > pu) swap(pl, pu);

        //cout << u << " " << d << " " << pl << " " << pu << endl;
        //cout << u << " " << kthAncestor(u, d) << endl;

        ll leftPos  = lower_bound(vals.begin(), vals.end(), pl) - vals.begin() + 1;
        ll rightPos = upper_bound(vals.begin(), vals.end(), pu) - vals.begin();

        if (leftPos > N)
        {
            cout << 0 << endl;
            ans = 0;
            continue;
        }

        if (rightPos > N)
        {
            rightPos = N;
        }


        //cout << leftPos << " " << rightPos << endl;
        
        ll prothom = pst.getSum(root[kthAncestor(u, d + 1)], leftPos, rightPos, 1, N);

        ll sec = pst.getSum(root[u], leftPos, rightPos, 1, N);

        //cout << prothom << " " << sec << endl;

        ans = sec - prothom;

        cout << ans << endl;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll cases = 1;
    //cin >> cases;

    while (cases--)
    {
        solve();
    }
}