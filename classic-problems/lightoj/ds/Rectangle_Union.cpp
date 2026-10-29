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

void pre() {
    fact[0] = 1;
    for (int i = 1; i < MX; i++) fact[i] = (i * fact[i - 1]) % MOD;
    inv[MX - 1] = Bigmod(fact[MX - 1], MOD - 2LL, MOD);
    for (int i = MX - 2; i >= 0; i--) inv[i] = (inv[i + 1] * (i + 1LL)) % MOD;
}

ll nCr(ll n, ll r, ll p) { 
    if(r > n || r < 0) return 0;
    if(n == r || r == 0) return 1;
    return (((fact[n] * inv[r]) % p ) * inv[n - r]) % p;
}

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


Compression cmp;
vll y;
vll x;

struct SegTree
{
    ll sz = 0;
    vll res;
    vll cnt;
    ll dummy;

    void init(int n, ll d)
    {
        dummy = d;
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, 0);
        cnt.assign(sz * 2, 0);
    }

    void pull(int x, int lx, int rx)
    {
        ll cl;
        ll cr;
        if (rx >= cmp.vals.size() - 1)
        {
            cr = cmp.vals.back();
        }
        else cr = cmp.rev(rx + 1);

        if (lx >= cmp.vals.size() - 1)
        {
            cl = cmp.vals.back();
        }
        else cl = cmp.rev(lx);

        ll len = cr - cl;

        if (cnt[x] >= 1)
        {
            res[x] = len;
        }

        else if (cnt[x] == 0)
        {
            if (lx == rx) res[x] = 0;

            else
            res[x] = res[2 * x + 1] + res[2 * x + 2];
        }
    }

    void update(int l, int r, ll v, int x, int lx, int rx)
    {
        if (r < lx || rx < l) return;

        if (lx >= l && rx <= r)
        {
            cnt[x] += v;
            pull(x, lx, rx);
            return;
        }

        ll mid = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, mid);
        update(l, r, v, 2 * x + 2, mid + 1, rx);

        pull(x, lx, rx);

        //res[x] = op(res[2 * x + 1], res[2 * x + 2]);
    }
};

SegTree st;

struct Event{
    ll x, y1, y2;
    ll e;
};

void solve()
{
    ll n;
    cin >> n;

    y.clear();

    vector<Event> ev;

    FOR(i, 0, n)
    {
        ll x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        ev.pb({x1, y1, y2, 1});
        ev.pb({x2, y1, y2, -1});
        y.pb(y1); y.pb(y2);
    }

    cmp.build(y);
    st.init(cmp.vals.size() - 1, 0);

    sort(ev.begin(), ev.end(), [](Event &a, Event &b){
        return a.x < b.x;
    });

    ll ans = 0;

    FOR(i, 0, ev.size())
    {
        ll x = ev[i].x;
        ll y1 = ev[i].y1;
        ll y2 = ev[i].y2;
        ll e = ev[i].e;

        ll cy1 = cmp.get(y1);
        ll cy2 = cmp.get(y2) - 1;

        if (i == 0)
        {
            st.update(cy1, cy2, e, 0, 0, st.sz - 1);
        }

        else
        {
            ll diff = x - ev[i - 1].x;

            ans += st.res[0] * diff;

            st.update(cy1, cy2, e, 0, 0, st.sz - 1);
        }
    }

    cout << ans << endl;

}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        cout << "Case " << i << ": ";
        solve();
    }
}