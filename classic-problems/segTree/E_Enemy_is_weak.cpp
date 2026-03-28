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
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
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
const ld PI = acos((ld) -1);
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;

ll Bigmod(ll a, ll b, ll m){
    if(b == 0) return 1 % m;
    ll x = Bigmod(a, b / 2LL, m);
    x = (x * x) % m;
    if(b % 2 == 1) x = (x * a) % m;
    return x;
}

ll fact[MX];
ll inv[MX];
vpll mv = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

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
    vll sum;

    SegTree(int n)
    {
        sz = 1;
        while (sz < n) sz *= 2;
        sum.assign(sz * 2, 0);
    }

    void build(vll &a, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < a.size())
            sum[x] = a[lx];
            return; 
        }

        ll mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        sum[x] = sum[2 * x + 1] + sum[2 * x + 2];
    }

    void assign(int i, int v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            sum[x]++;
            return;
        }

        ll mid = (lx + rx) / 2;

        if (i < mid) assign(i, v, 2 * x + 1, lx, mid);
        else assign(i, v, 2 * x + 2, mid, rx);

        sum[x] = sum[2 * x + 1] + sum[2 * x + 2];
    }

    ll getSum(int l, int r, int x, int lx, int rx)
    {
        if (r <= lx || rx <= l) return 0;

        if (lx >= l && rx <= r)
        {
            return sum[x];
        }

        if (rx - lx == 1)
        {
            return sum[x];
        }

        ll mid = (lx + rx) / 2;

        return getSum(l, r, 2 * x + 1, lx, mid) + getSum(l, r, 2 * x + 2, mid, rx);
    }
};

vll temp;

void solve()
{
    ll n;
    cin >> n;
    
    vll a(n);
    
    FOR(i, 0, n)
    {
        cin >> a[i];
    }

    vll b(n);

    //s1.assign(0, 1, 0, 0, s1.sz);

    temp.resize(n);

    FOR(i, 0, n)
        temp[i] = a[i];

    sort(temp.begin(), temp.end());

    unordered_map<ll, ll, custom_hash> ids;

    ll id = 0;

    FOR(i, 0, n) 
    {
        if (ids.find(temp[i]) == ids.end()) 
        {
            ids[temp[i]] = id;
            id++;
        }
    }

    SegTree s1(id), s2(id);

    s1.build(b, 0, 0, s1.sz);
    s2.build(b, 0, 0, s2.sz);

    FOR(i, 0, n)
    {
        s1.assign(ids[a[i]], -1, 0, 0, s1.sz);
    }

    ll ans = 0;

    FOR(i, 0, n)
    {
        s2.assign(ids[a[i]], -1, 0, 0, s2.sz);

        ll curId = ids[a[i]];
        ans += (i + 1 - s2.getSum(0, curId + 1, 0, 0, s2.sz)) *
               (s1.getSum(0, curId, 0, 0, s1.sz) - s2.getSum(0, curId, 0, 0, s2.sz));
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

    while (cases--)
    {
        solve();
    }
}