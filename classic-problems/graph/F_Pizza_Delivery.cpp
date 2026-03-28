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

void solve()
{
    ll n, ax, ay, bx, by;
    cin >> n >> ax >> ay >> bx >> by;

    vll px(n), py(n);

    FOR(i, 0, n) cin >> px[i];
    FOR(i, 0, n) cin >> py[i];

    map<ll, vll> all;

    FOR(i, 0, n)
    {
        all[px[i]].pb(py[i]);
    }

    vpll cols(all.size());
    int ind = 0;

    for (auto it = all.begin(); it != all.end(); it++)
    {
        sort(it->ss.begin(), it->ss.end());
        cols[ind].ff = it->ss[0];
        cols[ind].ss = it->ss[it->ss.size() - 1];
        ind++;
    }

    // FOR(i, 0, cols.size())
    // cout << cols[i].ff << " " << cols[i].ss << endl;

    ll ans = bx - ax;

    ll levels = cols.size() - 1;

    vll upDp(cols.size(), 0);
    vll downDp(cols.size(), 0);

    upDp[levels] = abs(cols[levels].ss - by);
    downDp[levels] = abs(cols[levels].ff - by);

    FORR(i, (ll) cols.size() - 2, 0)
    {
        ll dist = abs(cols[i + 1].ss - cols[i + 1].ff);

        upDp[i] = dist + abs(cols[i + 1].ss - cols[i].ss) + downDp[i + 1];
        downDp[i] = dist + abs(cols[i + 1].ff - cols[i].ff) + upDp[i + 1];

        upDp[i] = min(upDp[i], dist + abs(cols[i + 1].ff - cols[i].ss) + upDp[i + 1]);
        downDp[i] = min(downDp[i], dist + abs(cols[i + 1].ss - cols[i].ff) + downDp[i + 1]);
    }

    ll dist = cols[0].ss - cols[0].ff;

    ll up = dist + abs(cols[0].ss - ay) + downDp[0];
    ll down = dist + abs(cols[0].ff - ay) + upDp[0];

    // cout << up << " " << down << endl;
    // cout << upDp[0] << " " << downDp[0] << endl;

    cout << min(up, down) + ans << endl;



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