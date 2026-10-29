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

vector<int> spf(MX);

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

vector<int> getPrimeFactors(int x)
{
    vector<int> ret;
    while (x != 1) {
        ret.push_back(spf[x]);
        int p = spf[x];

        while (x % p == 0)
        x = x / p;
    }
    return ret;
}

vector<int> par, rnk, sz;

struct DSU 
{
    ll c;

    DSU(ll n)
    {
        par.assign(n + 1, 0);
        rnk.assign(n + 1, 0);
        sz.assign(n + 1, 0);

        FOR(i, 1, n + 1) par[i] = i;
    }

    ll find(ll i) 
    {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }

    bool same(ll i, ll j) 
    {
        return find(i) == find(j);
    }

    ll get_size(ll i) 
    {
        return sz[find(i)];
    }

    ll count() 
    {
        return c;    //connected components
    }

    void merge(ll i, ll j) 
    {
        if ((i = find(i)) == (j = find(j))) return;

        if (rnk[i] > rnk[j]) swap(i, j);

        par[i] = j;
        sz[j] += sz[i];
        c--;

        if (rnk[i] == rnk[j]) rnk[j]++;
    }
};

vector<bool> taken(MX);
vector<int> all(MX);

void solve()
{
    FOR(i, 0, MX)
    {
        taken[i] = false;
        all[i] = 0;
    }

    ll n;
    cin >> n;

    vll a(n + 1);
    FOR(i, 1, n + 1)
    {
        cin >> a[i];
        all[a[i]]++;
    }

    DSU dsu(MX);

    FOR(i, 1, n + 1)
    {
        if (a[i] == 1) continue;
        vi temp = getPrimeFactors(a[i]);

        for(auto p: temp)
        {
            if (!taken[p])
            {
                taken[p] = true;
                for (ll val = p; val <= MX; val += p)
                {
                    if (all[val] != 0) dsu.merge(val, a[i]);
                }
            }
        }
    }

    set<int> s;

    FOR(i, 2, MX)
    {
        if (all[i] != 0)
        {
            //cout << i << " " << dsu.find(i) << endl;
            s.insert(dsu.find(i));
        }
    }

    ll comp = s.size() + all[1];

    //cout << comp << endl;
    cout << (Bigmod(2, comp, MOD) - 2 + MOD) % MOD << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    sieve();

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}