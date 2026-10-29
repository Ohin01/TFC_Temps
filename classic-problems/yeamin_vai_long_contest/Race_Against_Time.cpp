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

struct FenTree // 1-based currently
{
    vector<ordered_set<pi>> sum;
    int sz;

    void init(int n)
    {
        sum.assign(n + 1, ordered_set<pi>());
        sz = n;
    }

    void update(int ind, pi x)
    {
        while (ind <= sz) //ind < sz
        {
            sum[ind].insert(x);
            ind += (ind & (-ind)); //ind |= (ind + 1);
        }
    }

    void dlt(int ind, pi x)
    {
        while (ind <= sz) //ind < sz
        {
            sum[ind].erase(x);
            ind += (ind & (-ind)); //ind |= (ind + 1);
        }
    }

    ll query(int ind, int x)
    {
        ll ans = 0;
        pi p = {x + 1, -1};
        while (ind > 0) //ind >= 0
        {
            ans += sum[ind].order_of_key(p);
            ind -= (ind & (-ind)); //ind = (ind & (ind + 1)) - 1;
        }
        return ans;
    }

    ll query(int l, int r, int x)
    {
        //if (l == 0) return query(r);
        return query(r, x) - query(l - 1, x);
    }
};

void solve()
{
    ll n, q;
    cin >> n >> q;

    vll a(n + 1);
    FOR(i, 1, n + 1) cin >> a[i];

    FenTree ft;
    ft.init(n + 1);

    int id = 0;
    vpi all(n + 1);

    FOR(i, 1, n + 1)
    {
        pi p = {a[i], id++};
        all[i] = p;

        ft.update(i, p);
    }

    while (q--)
    {
        char c;
        cin >> c;

        if (c == 'C')
        {
            int l, r, x;
            cin >> l >> r >> x;

            cout << ft.query(l, r, x) << endl;
        }

        else
        {
            int ind, val;
            cin >> ind >> val;

            pi dlt = all[ind];
            ft.dlt(ind, dlt);

            pi ins = {val, id++};
            ft.update(ind, ins);
            all[ind] = ins;
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

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}