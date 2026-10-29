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

const int N = 1e5 + 5;
const int LOG = 18;

struct Node {
    int val1, idx1;  // largest
    int val2, idx2;  // 2nd largest
};

Node t[N][LOG];
int a[N];

Node combine(Node A, Node B) {
    // Collect up to 4 candidates (value, index)
    vector<pair<int,int>> v = {
        {A.val1, A.idx1},
        {A.val2, A.idx2},
        {B.val1, B.idx1},
        {B.val2, B.idx2}
    };

    // Remove invalid entries (-1 index)
    v.erase(remove_if(v.begin(), v.end(),
                      [](auto &p){ return p.second == -1; }),
            v.end());

    // Sort by value descending
    sort(v.begin(), v.end(), [](auto &x, auto &y) {
        if (x.first != y.first) 
            return x.first > y.first;   // sort by first descending
        return x.second > y.second;     // tie-break by second descending
    });

    Node res = {-1, -1, -1, -1};
    if (!v.empty()) {
        res.val1 = v[0].first;
        res.idx1 = v[0].second;
    }
    // find 2nd distinct index
    for (auto &p : v) {
        if (p.second != res.idx1) {
            res.val2 = p.first;
            res.idx2 = p.second;
            break;
        }
    }
    return res;
}

void build(int n) {
    for (int i = 1; i <= n; ++i)
        t[i][0] = {a[i], i, -1, -1};

    for (int k = 1; k < LOG; ++k) {
        for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
            t[i][k] = combine(t[i][k - 1],
                              t[i + (1 << (k - 1))][k - 1]);
        }
    }
}

Node query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return combine(t[l][k], t[r - (1 << k) + 1][k]);
}

void solve()
{
    int n;
    cin >> n;

    int arr[n + 1];
    for(int i = 1; i <= n; i++) cin >> arr[i];

    FOR(i, 1, n + 1)
    a[i] = arr[i] - i;

    build(n);

    ll ans = -1;

    // FOR(i, 1, n + 1)
    // cout << a[i] << " ";
    // cout << endl;

    FOR(i, 1, n - 1)
    {
        Node p = query(i + 1, n);

        //cout << p.val1 << " " << p.idx1 << endl;
        //cout << p.val2 << " " << p.idx2 << endl;
         ans = max(ans, a[i] + p.val1 + p.val2 + 2 * i + min(p.idx1 - i + 1, p.idx2 - i + 1));

         //cout << ans << endl;
         //cout << endl;
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

    while (cases--)
    {
        solve();
    }
}