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

ll n, h;
vll ht(2010);
ll oned[2010][2010];
ll twod[2010][2010];
map<ll, ll> inds;

ll func1(ll l, ll r, ll hind)
{
    ll cur = inds[hind];

    if (hind <= 1) return 0;
    if (cur == 1) return 0;
    if (l < 1 || r > n) return 0;
    if (l > n || r < 1) return 0;
    if (l > r) return 0;

    ll niche = inds[hind - 1];

    //cout << cur << " " << niche << endl;

    vll ans;
    ll last = l - 1;

    FOR(i, l, r + 1)
    {
        if (ht[i] == cur)
        {
            //cout << l << " " << r << " " << hind << " " << cur << " " << ht[i] << endl;
            ans.pb((i - 1 - last) * (cur - niche) + func1(last + 1, i - 1, hind - 1));
            last = i;
        }
    }

    ans.pb((r - last) * (cur - niche) + func1(last + 1, r, hind - 1));

    sort(ans.begin(), ans.end(), greater<ll>());

    ans.pb(0);

    oned[l][r] = ans[0];

    return ans[0] + ans[1];
}

ll func2(ll l, ll r, ll hind)
{
    ll cur = inds[hind];

    if (hind <= 1) return 0;
    if (cur == 1) return 0;
    if (l < 1 || r > n) return 0;
    if (l > n || r < 1) return 0;
    if (l > r) return 0;

    ll niche = inds[hind - 1];

    //cout << cur << " " << niche << endl;

    vll ans;
    ll last = l - 1;

    FOR(i, l, r + 1)
    {
        if (ht[i] == cur)
        {
            //cout << l << " " << r << " " << hind << " " << cur << " " << ht[i] << endl;
            ans.pb((i - 1 - last) * (cur - niche) + func2(last + 1, i - 1, hind - 1));
            last = i;
        }
    }

    ans.pb((r - last) * (cur - niche) + func2(last + 1, r, hind - 1));

    sort(ans.begin(), ans.end(), greater<ll>());

    ans.pb(0);

    return ans[0];
}

ll calc(ll l, ll r, ll hind)
{
    ll cur = inds[hind];

    if (hind <= 1) return 0;
    if (cur == 1) return 0;
    if (l < 1 || r > n) return 0;
    if (l > n || r < 1) return 0;
    if (l > r) return 0;

    ll niche = inds[hind - 1];

    //cout << cur << " " << niche << endl;

    vll ans;
    ll last = l - 1;
    ll mx = 0;

    FOR(i, l, r + 1)
    {
        if (ht[i] == cur)
        {
            //cout << l << " " << r << " " << hind << " " << cur << " " << ht[i] << endl;
            ans.pb((i - 1 - last) * (cur - niche) + func2(last + 1, i - 1, hind - 1));
            mx = max(mx, (i - 1 - last) * (cur - niche) + func1(last + 1, i - 1, hind - 1));
            last = i;
        }
    }

    ans.pb((r - last) * (cur - niche) + func2(last + 1, r, hind - 1));
    mx = max(mx, (r - last) * (cur - niche) + func1(last + 1, r, hind - 1));

    sort(ans.begin(), ans.end(), greater<ll>());

    ans.pb(0);

    return max(ans[0] + ans[1], mx);
}

void solve()
{
    inds.clear();
    cin >> n >> h;

    FOR(i, 0, n + 1)
    {
        FOR(j, 0, n + 1)
        {
            oned[i][j] = -1;
            twod[i][j] = -1;
        }
    }

    FOR(i, 1, n + 1) cin >> ht[i];

    vll sr;
    FOR(i, 1, n + 1) sr.pb(ht[i]);
    sort(sr.begin(), sr.end());

    ll cnt = 1;
    FOR(i, 0, n)
    {
        auto it = inds.find(sr[i]);

        if (it == inds.end())
        {
            inds[cnt] = sr[i];
            cnt++;
        } 

        else continue;
    }

    ll mx = inds[cnt - 1];

    inds[cnt] = h;
    cnt++;

    // for (auto p: inds) cout << p.ff << " " << p.ss << endl;
    // cout << cnt << endl;

    //cout << func(1, 1, 2) << endl;

    cout << calc(1, n, cnt - 1) << endl;


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