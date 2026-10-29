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

typedef long long       ll;
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
const int LOGN = 20;
const ld PI = acos((ld) -1);

ll fact[MX];
ll inv[MX];
vpll mv = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

ll Bigmod(ll a, ll b, ll m){
    if(b == 0) return 1 % m;
    ll x = Bigmod(a, b / 2LL, m);
    x = (x * x) % m;
    if(b % 2 == 1) x = (x * a) % m;
    return x;
}

void pre(){
    fact[0]=1;
    inv[0]=1;
    FOR(i, 1, MX){
        fact[i] = (i * fact[i - 1])% MOD;
        inv[i] = Bigmod(fact[i], MOD - 2LL, MOD);
    }
}

ll nCr(ll n, ll r, ll p) { 
    if(r > n || r < 0) return 0;
    if(n == r || r == 0) return 1;
    return (((fact[n] * inv[r]) % p ) * inv[n - r]) % p;
}

struct SegTree
{
    ll sz = 0;
    vll res;
    ll dummy;

    void init(int n, ll d)
    {
        dummy = d;
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, d);
    }

    ll op(ll a, ll b)
    {
        return max(a, b);
    }

    void build(vll &a, int x, int lx, int rx)
    {
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

    void update(int i, ll v, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            res[x] = v;
            return;
        }

        ll mid = (lx + rx) / 2;

        if (i <= mid) update(i, v, 2 * x + 1, lx, mid);
        else update(i, v, 2 * x + 2, mid + 1, rx);

        res[x] = op(res[2 * x + 1], res[2 * x + 2]);
    }

    ll query(int l, int r, int x, int lx, int rx)
    {
        if (r < lx || rx < l) 
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

ll nn, q;
vll id(MAX, -1);
vll ind(MAX, -1);

ll func(vpll &line, vpll &intervals)
{
    ll tot = 0;
    ll n = line.size();
    vll vals(n + 10);

    FOR(i, 0, n)
    {
        vals[i + 1] = line[i].ss; 
        tot += vals[i + 1];
    }

    vll pref(n + 10, 0);

    FOR(i, 1, n + 4)
    {
        pref[i] = pref[i - 1] + vals[i];
    }

    vll rights(n + 10, n - 1);

    FOR(i, 0, intervals.size())
    {
        ll l = intervals[i].ff + 1;
        ll r = intervals[i].ss + 1;

        rights[l] = min(rights[l], r - 2);
    }

    //1 2 3 4 5 6
    //5 4 5 6 3 0

    //[1, 4], [2, 6], [3, 6]

    //FOR(i, 1, n + 1) cout << rights[i] << " "; cout << endl;

    SegTree st;
    st.init(n + 10, -1);

    vll dp(n + 10, 0);

    st.update(n, pref[n], 0, 0, st.sz - 1);
    st.update(n - 1, pref[n - 1], 0, 0, st.sz - 1);

    FORR(i, n, 1)
    {
        if (rights[i] < i) dp[i] = dp[i + 1];
        else dp[i] = max(dp[i + 1], st.query(i, rights[i], 0, 0, st.sz - 1) - pref[i - 1]);

        if (i - 2 >= 1)
        st.update(i - 2, pref[i - 2] + dp[i], 0, 0, st.sz - 1);

        //cout << i << " " << dp[i] << endl;
    }

    return tot - dp[1];
}

void solve()
{
    cin >> nn >> q;

    deque<pll> dq;
    ll tot = 0;

    FOR(i, 1, nn + 1)
    {
        ll val;
        cin >> val;

        tot += val;

        dq.pb({i, val});
    }

    FOR(i, 0, dq.size())
    {
        pll p = dq[i];

        if (p.ss == 0)
        {
            FOR(j, 0, i + 1)
            {
                pll t = dq.front();
                dq.pop_front();
                dq.push_back(t);
            }

            break;
        }
    }

    vector<vector<pll>> all;

    vpll temp;

    FOR(i, 0, nn)
    {
        temp.pb(dq[i]);

        if (dq[i].ss == 0)
        {
            all.pb(temp);
            temp.clear();
        }
    }

    FOR(i, 0, all.size())
    {
        FOR(j, 0, all[i].size())
        {
            id[all[i][j].ff] = i;
            ind[all[i][j].ff] = j;
            //cout << all[i][j].ff << " " << all[i][j].ss << endl;
        }
        //cout << endl;
    }

    vector<vpll> ints(all.size() + 1);
    
    while (q--)
    {
        ll l, r;
        cin >> l >> r;

        if (id[l] != id[r]) continue;

        ll k = id[l];

        l = ind[l], r = ind[r];
        //cout << l << " " << r << endl;

        if (l > r) swap(l, r);

        ints[k].pb({l, r});
    }

    ll ans = 0;

    FOR(i, 0, all.size())
    {
        if (ints[i].empty() == false)
        ans += func(all[i], ints[i]);
    }

    cout << ans << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}