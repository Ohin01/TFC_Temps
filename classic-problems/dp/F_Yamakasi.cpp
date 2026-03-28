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

const int N = 2e5 + 9;
int a[N];
pair<int, int> t2[N][18]; // {value, index}

pair<int, int> combine(pair<int, int> L, pair<int, int> R) {
    int val = max(L.first, R.first);

    if (val == L.first && val == R.first)
        return {val, min(L.second, R.second)};
    else if (val == L.first)
        return L;
    else if (val == R.first)
        return R;
    else
        return {val, min(L.second, R.second)};
}

void build(int n) {
    for (int i = 1; i <= n; ++i)
        t2[i][0] = {a[i], i};
    for (int k = 1; k < 18; ++k) {
        for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
            t2[i][k] = combine(t2[i][k - 1], t2[i + (1 << (k - 1))][k - 1]);
        }
    }
}

pair<int, int> query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return combine(t2[l][k], t2[r - (1 << k) + 1][k]);
}

void solve()
{
    ll n;
    cin >> n;

    ll x, k;
    cin >> x >> k;
    FOR(i, 1, n + 1) cin >> a[i];

    build(n);

    map<ll, vll> freq;
    map<ll, ll> pos;
    freq[0].pb(0);

    vll pref(n + 1);
    ll ans = 0;
    FOR(i, 1, n + 1)
    {
        pref[i] = pref[i - 1] + a[i];

        auto it = freq.find(pref[i] - x);

        if (it != freq.end())
        {
            //for (auto c: it->ss) pos.insert({c + 1, i});
            vll &arr = it->ss;
            
            ll lo = 0;
            ll hi = arr.size() - 1;

            ll fir = -1;

            while (lo <= hi)
            {
                ll mid = lo + (hi - lo) / 2;

                if (query(arr[mid] + 1, i).ff < k)
                {
                    hi = mid - 1;
                }

                else if (query(arr[mid] + 1, i).ff > k)
                {
                    lo = mid + 1;
                }

                else
                {
                    fir = mid;
                    lo = mid + 1;
                }
            }

            if (fir == -1)
            {
                freq[pref[i]].pb(i);
                continue;
            }

            ll last = 0;
            lo = 0, hi = arr.size() - 1;

            while (lo <= hi)
            {
                ll mid = lo + (hi - lo) / 2;

                if (query(arr[mid] + 1, i).ff < k)
                {
                    hi = mid - 1;
                }

                else if (query(arr[mid] + 1, i).ff > k)
                {
                    lo = mid + 1;
                }

                else
                {
                    last = mid;
                    hi = mid - 1;
                }
            }

            ans += (fir - last + 1);
        }

        freq[pref[i]].pb(i);
    }

    cout << ans << endl;

    //for (auto p: pos) cout << p.ff << " " << p.ss << endl;



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
        solve();
    }
}