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

vector<ll> spf(MX);

void sieve()
{
    for (int i = 0; i < MX; i++) spf[i] = i;

    for (int i = 2; i * i < MX; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MX; j += i) {
                if (spf[j]== j)
                    spf[j] = i;
            }
        }
    }
}

ll getPrimeFactors(int x)
{
    unordered_map<ll, ll, custom_hash> cnt;
    while (x != 1) {
        cnt[spf[x]]++;
        x = x / spf[x];
    }
    ll ans = 1;
    for (auto &p: cnt)
    {
        ans *= (p.ss + 1);
    }
    return ans;
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
        return a + b;
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

    void update(int l, int r, int x, int lx, int rx)
    {
        if (r < lx || rx < l) return;

        if (lx == rx)
        {
            res[x] = getPrimeFactors(res[x]);
            return;
        }

        if (lx >= l && rx <= r && (rx - lx + 1) * 2LL == res[x])
        {
            return;
        }

        ll mid = (lx + rx) / 2;

        update(l, r, 2 * x + 1, lx, mid);
        update(l, r, 2 * x + 2, mid + 1, rx);

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

void solve()
{
    ll n;
    cin >> n;

    ll q;
    cin >> q;

    vll a(n + 1);
    FOR(i, 1, n + 1) cin >> a[i];

    vll pref(n + 1, 0);
    FOR(i, 1, n + 1)
    {
        if (a[i] == 1)
        {
            pref[i] = pref[i - 1] + 1;
            a[i] = 2;
        }

        else pref[i] = pref[i - 1];
    }

    SegTree st;
    st.init(n + 10, 0);
    st.build(a, 0, 0, st.sz - 1);

    FOR(i, 1, q + 1)
    {
        ll t;
        cin >> t;

        ll l, r;
        cin >> l >> r;

        if (t == 1)
        {
            st.update(l, r, 0, 0, st.sz - 1);
        }

        else
        {
            cout << st.query(l, r, 0, 0, st.sz - 1) - (pref[r] - pref[l - 1]) << endl;
        }
    }

}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    sieve();

    // d[1] = 1;

    // FOR(i, 2, MX)
    // {
    //     d[i] = getPrimeFactors(i); 
    // }

    // cout << d[4] << " " << d[6] << endl;

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}