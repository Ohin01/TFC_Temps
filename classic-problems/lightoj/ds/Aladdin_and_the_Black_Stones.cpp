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

const ll MOD = (1LL<<32);//998244353;
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

template <typename T> 
struct BIT2D 
{
	const int n, m;
	vector<vector<T>> bit;

	BIT2D(int n, int m) : n(n), m(m), bit(n + 1, vector<T>(m + 1)) {}

	/** adds val to the point (r, c) */
	void add(int r, int c, T val) {
		for (; r <= n; r += r & -r) {
			for (int i = c; i <= m; i += i & -i) { bit[r][i] += val; bit[r][i] % MOD;}
		}
	}

	/** @returns sum of points with row in [1, r] and column in [1, c] */
	T rect_sum(int r, int c) {
		T sum = 0;
		for (; r > 0; r -= r & -r) {
			for (int i = c; i > 0; i -= i & -i) { sum += bit[r][i]; }
		}
		return sum;
	}

	/** @returns sum of points with row in [r1, r2] and column in [c1, c2] */
	T rect_sum(int r1, int c1, int r2, int c2) {
        if (r1 > r2 || c1 > c2) return 0;
		return (rect_sum(r2, c2) - rect_sum(r2, c1 - 1) - rect_sum(r1 - 1, c2) +
		       rect_sum(r1 - 1, c1 - 1) + MOD) % MOD;
	}
};

void solve()
{
    ll n;
    cin >> n;

    vll w(n + 1);
    FOR(i, 1, n + 1) cin >> w[i];

    vector<tuple<ll, ll, ll>> all, temp;

    FOR(i, 1, n + 1)
    {
        FOR(j, i + 1, n + 1)
        {
            all.pb({w[i] + w[j], i, j});
        }
    }

    BIT2D<ll> dp(n + 1, n + 1);

    sort(all.begin(), all.end());

    ll prev = get<0>(all[0]);
    ll ans = 0;

    FOR(i, 0, all.size())
    {
        ll w = get<0>(all[i]);
        ll l = get<1>(all[i]);
        ll r = get<2>(all[i]);

        if (prev != w)
        {
            FOR(j, 0, temp.size())
            {
                ll w1 = get<0>(temp[j]);
                ll l1 = get<1>(temp[j]);
                ll r1 = get<2>(temp[j]); 
                dp.add(l1, r1, w1);
            }
            temp.clear();
        }

        ll val;

        if (l == r - 1 || l == r - 2) val = 1;
        else val = dp.rect_sum(l + 1, l + 1, r - 1, r - 1) + 1;

        val %= MOD;
        // ans += val;
        // ans %= MOD;

        prev = w;

        temp.pb({val, l, r});

        //cout << w << " " << l << " " << r << " " << val << endl;
    }

    FOR(j, 0, temp.size())
    {
        ll w1 = get<0>(temp[j]);
        ll l1 = get<1>(temp[j]);
        ll r1 = get<2>(temp[j]); 
        dp.add(l1, r1, w1);
    }
    temp.clear();

    cout << dp.rect_sum(n, n) % MOD << endl;
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