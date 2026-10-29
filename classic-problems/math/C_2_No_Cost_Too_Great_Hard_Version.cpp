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
const int MAX = 2e5 + 2;
const int MX = 4e5 + 5;
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

vector<ll> getPrimeFactors(int x)
{
    vector<ll> ret;
    while (x != 1) {
        ll p = spf[x];
        ret.push_back(spf[x]);

        while (x % p == 0)
        x = x / p;
    }
    return ret;
}

void solve()
{
    ll n;
    cin >> n;

    vll a(n + 1), b(n + 1);

    FOR(i, 1, n + 1) cin >> a[i];
    FOR(i, 1, n + 1) cin >> b[i];

    map<ll, ll> cnt;
    
    FOR(i, 1, n + 1)
    {
        vll temp = getPrimeFactors(a[i]);

        for (auto p: temp) 
        {
            cnt[p]++;
            if (cnt[p] >= 2)
            {
                cout << 0 << endl;
                return;
            }
        }
    }

    ll ans = INF;

    vpll odd, all;
    FOR(i, 1, n + 1)
    {
        if (a[i] % 2 == 1) odd.pb({b[i], a[i]});
        all.pb({b[i], a[i]});
    }

    sort(odd.begin(), odd.end());
    sort(all.begin(), all.end());

    if (odd.size() >= 2) ans = min(ans, odd[0].ff + odd[1].ff);

    FOR(i, 0, min(3LL, n))
    {
        ll val = all[i].ss;
        ll co = all[i].ff;
        vll temp = getPrimeFactors(val);

        for (auto p: temp) cnt[p]--;

        for (auto &q: cnt)
        {
            int p = q.ff;
            int t = q.ss;
            if (t >= 1) ans = min(ans, ((p - (val % p)) % p) * co); 
        }

        for (auto p: temp) cnt[p]++;
    }
    
    FOR(i, 3, n)
    {
        ll val = all[i].ss;
        ll co = all[i].ff;
        
        vll temp = getPrimeFactors(val);

        for (auto p: temp) cnt[p]--;
            
        vll te = getPrimeFactors(val + 1);
            
        for (auto p: te)
        {
            if (cnt[p] >= 1) 
            {
                ans = min(ans, co);
                break;
            }
        }
    
        for (auto p: temp) cnt[p]++;
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

    sieve();

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}