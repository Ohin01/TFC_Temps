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

struct Mat {
    int n, m;
    vector<vector<int>> a;
    Mat() { }
    Mat(int _n, int _m) {n = _n; m = _m; a.assign(n, vector<int>(m, 0)); }
    Mat(vector< vector<int> > v) { n = v.size(); m = n ? v[0].size() : 0; a = v; }

    inline void make_unit() 
    {
        assert(n == m);
        for (int i = 0; i < n; i++)  
        {
            for (int j = 0; j < n; j++) 
                a[i][j] = i == j;
        }
    }

    inline Mat operator + (const Mat &b) 
    {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for(int i = 0; i < n; i++) 
        {
            for(int j = 0; j < m; j++) 
            {
                ans.a[i][j] = (a[i][j] + b.a[i][j]) % MOD;
            }
        }
        return ans;
    } 

    inline Mat operator - (const Mat &b) 
    {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for(int i = 0; i < n; i++) 
        {
            for(int j = 0; j < m; j++) 
            {
                ans.a[i][j] = (a[i][j] - b.a[i][j] + MOD) % MOD;
            }
        }
        return ans;
    }

    inline Mat operator * (const Mat &b) 
    {
        assert(m == b.n);
        Mat ans = Mat(n, b.m);
        for(int i = 0; i < n; i++) 
        {
            for(int j = 0; j < b.m; j++) 
            {
                for(int k = 0; k < m; k++) 
                {
                    ans.a[i][j] = (ans.a[i][j] + 1LL * a[i][k] * b.a[k][j] % MOD) % MOD;
                }
            }
        }
        return ans;
    }

    inline Mat pow(long long k) 
    {
        assert(n == m);
        Mat ans(n, n), t = a; ans.make_unit();
        while (k) 
        {
            if (k & 1) ans = ans * t;
            t = t * t;
            k >>= 1;
        }
        return ans;
    }
    
    inline Mat& operator += (const Mat& b) { return *this = (*this) + b; }
    inline Mat& operator -= (const Mat& b) { return *this = (*this) - b; }
    inline Mat& operator *= (const Mat& b) { return *this = (*this) * b; }
    inline bool operator == (const Mat& b) { return a == b.a; }
    inline bool operator != (const Mat& b) { return a != b.a; }
};

void solve()
{
    ll n, k;
    cin >> n >> k;

    Mat mat(n, n);
    Mat ini(n, 1);

    FOR(i, 0, n)
    {
        FOR(j, 0, n)
        {
            cin >> mat.a[j][i];
        }
    }

    FOR(i, 0, n) ini.a[i][0] = 1;

    ini = mat.pow(k) * ini;
    //ini2 = mat.pow(k - 1) * ini2;

    ll res = 0;

    FOR(i, 0, n)
    {
        res += ini.a[i][0];
        res %= MOD;
    }
    //ll res2 = ini2.a[n - 1][0];

    cout << (res) % MOD << endl;
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