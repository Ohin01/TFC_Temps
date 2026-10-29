#include<bits/stdc++.h>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    template<typename T, typename U>
    size_t operator()(const pair<T, U>& x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();

        uint64_t h1 = splitmix64((uint64_t)x.first + FIXED_RANDOM);
        uint64_t h2 = splitmix64((uint64_t)x.second + FIXED_RANDOM);

        return h1 ^ (h2 >> 1);
    }
};

typedef int      ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;
typedef vector<bool>    vb;
typedef vector<vb>      vvb;
typedef pair<int, int>  pi;
typedef vector<pi>      vpi;
typedef pair<ll, ll>    pll;
typedef vector<pll>     vpll;

#define pb              push_back
#define ff              first
#define ss              second
#define index           find_by_order
#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)
#define YES             cout << "YES\n"
#define NO              cout << "NO\n"
#define lcm(a, b)       ((a / __gcd(a, b)) * b)

const ll MOD = 1e9 + 7;//998244353;
const ll INF = 9e18;
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 18;
const ld PI = acos((ld) -1);

struct FenTree // 1-based currently
{
    vector<ll> sum;
    int sz;

    void init(int n)
    {
        sum.assign(n + 1, 0);
        sz = n;
    }

    void update(int ind, ll x)
    {
        while (ind <= sz) //ind < sz
        {
            sum[ind] += x;
            ind += (ind & (-ind)); //ind |= (ind + 1);
        }
    }

    ll query(int ind)
    {
        ll ans = 0;
        while (ind > 0) //ind >= 0
        {
            ans += sum[ind];
            ind -= (ind & (-ind)); //ind = (ind & (ind + 1)) - 1;
        }
        return ans;
    }

    ll query(int l, int r)
    {
        //if (l == 0) return query(r);
        return query(r) - query(l - 1);
    }

    int lowerBound(int v)
    {
        int pos = 0; // pos = -1
        ll tot = 0;

        FORR(i, LOGN, 0)
        {
            if (pos + (1<<i) <= sz && tot + sum[pos + (1<<i)] < v)  // < sz
            {
                tot += sum[pos + (1<<i)];
                pos += (1<<i);
            }
        }
        return pos + 1; //pos gives the highest lower number
    }
};

const int N = 1e6 + 9, B = 650;
vector<int> graph[MAX];
int par[MAX][18];
int depth[MAX];
int starts[MAX], ens[MAX];
int euler[MX];
int cnt[MAX], a[MAX];
FenTree ft;
int ti = 1;
bool onAse[MAX];
int ans[MAX];

void dfs(int node, int parent)
{
    starts[node] = ti;
    euler[ti++] = node;
    par[node][0] = parent;

    for (auto ch: graph[node])
    {
        if (ch == parent) continue;
        depth[ch] = depth[node] + 1;
        dfs(ch, node);
    }

    ens[node] = ti;
    euler[ti++] = node;
}

void fillAncestor(int n)
{
    FOR(i, 1, LOGN)
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

int kthAncestor(int node, int k)
{
    int ans = node;

    FOR(i, 0, LOGN)
    {
        if ((k & (1<<i)) != 0)
        {
            ans = par[ans][i];
            if (ans == 0) return 0;
        }
    }

    return ans;
}

int LCA(int n1, int n2)
{
    if (depth[n1] > depth[n2]) swap(n1, n2);

    int diff = depth[n2] - depth[n1];
    n2 = kthAncestor(n2, diff);

    if (n1 == n2) return n1;

    FORR(i, LOGN - 1, 0)
    {
        if (par[n1][i] != par[n2][i])
        {
            n1 = par[n1][i];
            n2 = par[n2][i];
        }
    }

    return par[n1][0];
}


struct query 
{
    int l, r, id, a, b, lc;
    bool operator < (const query &x) const 
    {
        if(l / B == x.l / B) return ((l / B) & 1) ? r > x.r : r < x.r;
        return l / B < x.l / B;
    }
} Q[MAX];

unordered_map<ll, ll, custom_hash> mp;

void toggle(int i)
{
    int node = euler[i];
    int x = a[node];
    if (onAse[node]) 
    {
        mp[cnt[x]]--;
        cnt[x]--;

        if (cnt[x] > 0)
        mp[cnt[x]]++;
    }
    else 
    {
        if (cnt[x] > 0)
        mp[cnt[x]]--;
        cnt[x]++;
        mp[cnt[x]]++;
    }
    onAse[node] = !onAse[node];
}

void apply()
{
    for (auto &p: mp)
    {
        if (p.ss != 0) ft.update(p.ff, p.ss);
    }

    mp.clear();
}

int32_t main() 
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    mp.clear();

    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];

    FOR(i, 0, n - 1)
    {
        ll u, v;
        cin >> u >> v;

        graph[u].pb(v);
        graph[v].pb(u);
    }
    dfs(1, 0);
    fillAncestor(n);
    ft.init(n + 10);

    for(int i = 1; i <= q; i++) 
    {
        ll st, en, l1, r1;
        cin >> st >> en >> l1 >> r1;

        Q[i].id = i;
        Q[i].a = l1;
        Q[i].b = r1;

        if (starts[st] > starts[en]) swap(st, en);
        
        int lca = LCA(st, en);
        Q[i].lc = starts[lca];
        if (lca == st)
        {
            Q[i].l = starts[st];
            Q[i].r = starts[en];
        }

        else
        {
            Q[i].l = ens[st];
            Q[i].r = starts[en];
        }
    }
    sort(Q + 1, Q + q + 1);
    int l = 1, r = 0;

    for(int i = 1; i <= q; i++) 
    {
        int L = Q[i].l, R = Q[i].r;
        int l1 = Q[i].a, r1 = Q[i].b;
        if(R < l) 
        {
            while (l > L) toggle(--l);
            while (l < L) toggle(l++);
            while (r < R) toggle(++r);
            while (r > R) toggle(r--);
        } 
        else 
        {
            while (r < R) toggle(++r);
            while (r > R) toggle(r--);
            while (l > L) toggle(--l);
            while (l < L) toggle(l++);
        }

        apply();

        if (Q[i].lc != Q[i].l) 
        {
            toggle(Q[i].lc);
            apply();
        }
        ans[Q[i].id] = ft.query(l1, r1);
        if (Q[i].lc != Q[i].l) 
        {
            toggle(Q[i].lc);
            apply();
        }
    }
    for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
    return 0;
}