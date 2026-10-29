#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename dataType>
using ordered_set = tree<dataType, null_type, less<dataType>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename dataType1, typename dataType2>
using ordered_map = tree<dataType1, dataType2, less<dataType1>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename dataType>
using ordered_multiset = tree<dataType, null_type, less_equal<dataType>, rb_tree_tag, tree_order_statistics_node_update>;

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

typedef int       ll;
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
const ll INF = 9e8;
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 20;
const ld PI = acos((ld) -1);

struct SegTree
{
    ll sz = 0;
    vll res;
    vll lazy;
    ll dummy;

    void init(int n, ll d)
    {
        dummy = d;
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, d);
        lazy.assign(sz * 2, 0);
    }

    ll op(ll a, ll b)
    {
        return max(a, b);
    }

    void push(int x, int lx, int rx)
    {
        if (lazy[x] == 0) return;

        res[x] += lazy[x];

        if (lx != rx)
        {
            lazy[2 * x + 1] += lazy[x];
            lazy[2 * x + 2] += lazy[x];
        }

        lazy[x] = 0;
    }

    void build(vll &a, int x, int lx, int rx)
    {
        lazy[x] = 0;

        if (lx == rx)
        {
            if (lx < (int)a.size())
            res[x] = a[lx];

            else
            res[x] = dummy;
            return; 
        }

        ll mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid + 1, rx);

        res[x] = op(res[2 * x + 1], res[2 * x + 2]);
    }

    void update(int l, int r, ll v, int x, int lx, int rx)
    {
        push(x, lx, rx);

        if (r < lx || rx < l) return;

        if (lx >= l && rx <= r)
        {
            lazy[x] += v;
            push(x, lx, rx);
            return;
        }

        ll mid = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, mid);
        update(l, r, v, 2 * x + 2, mid + 1, rx);

        res[x] = op(res[2 * x + 1], res[2 * x + 2]);
    }

    ll query(int l, int r, int x, int lx, int rx)
    {
        push(x, lx, rx);

        if (r < lx || rx < l || l > r) 
        {
            return dummy;
        }

        if (lx >= l && rx <= r)
        {
            return res[x];
        }

        ll mid = (lx + rx) / 2;

        return op(query(l, r, 2 * x + 1, lx, mid), query(l, r, 2 * x + 2, mid + 1, rx));
    }
};

void solve()
{
    ll n, k;
    cin >> n >> k;

    vll a(n + 1);
    FOR(i, 1, n + 1) cin >> a[i];

    vector<SegTree> st(k + 1);

    FOR(i, 0, k + 1) st[i].init(n + 1, 0);

    vvll dp(n + 1, vll(k + 1, 0));

    ll ans = -INF;

    dp[1][1] = 1;
    st[1].update(1, 1, 1, 0, 0, st[1].sz - 1);

    vll lst(n + 1, -1);

    lst[a[1]] = 1;

    FOR(i, 2, n + 1)
    {
        ll l = lst[a[i]] + 1;
        l = max(l, 1);

        ll r = i - 1;

        //cout << l << " " << r << endl;

        FOR(j, 1, k + 1)
        {
            if (j > i) break;

            if (j != 1)
            dp[i][j] = dp[i - 1][j - 1] + 1;

            if (l <= r) st[j].update(l, r, 1, 0, 0, st[j].sz - 1);

            dp[i][j] = max(dp[i][j], st[j].query(1, r, 0, 0, st[j].sz - 1));
            
            //if (l <= r) st[j - 1].update(l, r, -1, 0, 0, st[j - 1].sz - 1);

            if (dp[i - 1][j - 1] > 0) st[j].update(i, i, dp[i - 1][j - 1] + 1, 0, 0, st[j].sz - 1);
        }

        // cout << i << ": ";
        // FOR(j, 1, k + 1) cout << dp[i][j] << " "; cout << endl;

        // cout << i << "st : ";
        // FOR(j, 1, k + 1) cout << st[j].query(i, i, 0, 0, st[j].sz - 1) << " "; cout << endl;

        lst[a[i]] = i;
    }

    cout << dp[n][k] << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
   // cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}