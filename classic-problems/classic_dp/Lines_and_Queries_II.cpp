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

struct Line 
{
    ll m, c;
    Line(ll _m = 0, ll _c = -INF) : m(_m), c(_c) {}

    ll eval(ll x) const 
    {
        return (ll)(m * x + c);
    }
};

struct Node 
{
    Line line;
    Node *left, *right;
    Node(Line v)
    {
        line = v;
        left = right = NULL;
    }
};

struct LiChao 
{
    ll L, R;
    Node* root;

    LiChao(ll l, ll r) : L(l), R(r) 
    {
        root = new Node(Line()); // neutral line
    }

    void insert_line(Line nw, ll lx, ll rx, Node* node) 
    {
        ll mid = (lx + rx) >> 1;

        bool left = nw.eval(lx) > node->line.eval(lx);
        bool middle = nw.eval(mid) > node->line.eval(mid);

        if (middle) swap(nw, node->line);

        if (lx == rx) return;

        if (left != middle) 
        {
            if (!node->left) node->left = new Node(Line());
            insert_line(nw, lx, mid, node->left);
        } 
        else 
        {
            if (!node->right) node->right = new Node(Line());
            insert_line(nw, mid + 1, rx, node->right);
        }
    }

    void insert_segment(Line nw, ll ql, ll qr, ll lx, ll rx, Node* node) 
    {
        if (qr < lx || rx < ql) return;

        if (ql <= lx && rx <= qr) 
        {
            insert_line(nw, lx, rx, node);
            return;
        }

        ll mid = (lx + rx) >> 1;

        if (!node->left) node->left = new Node(Line());
        if (!node->right) node->right = new Node(Line());

        insert_segment(nw, ql, qr, lx, mid, node->left);
        insert_segment(nw, ql, qr, mid + 1, rx, node->right);
    }

    ll query_point(ll x, ll lx, ll rx, Node* node) 
    {
        if (!node) return -INF;

        ll res = node->line.eval(x);

        if (lx == rx) return res;

        ll mid = (lx + rx) >> 1;

        if (x <= mid && node->left)
            return max(res, query_point(x, lx, mid, node->left));

        if (x > mid && node->right)
            return max(res, query_point(x, mid + 1, rx, node->right));

        return res;
    }
};

void solve()
{
    ll n;
    cin >> n;

    LiChao lc(0, (1e9 + 7));

    while (n--)
    {
        ll q;
        cin >> q;

        if (q == 1) 
        {
            ll l, r, a, b;
            cin >> a >> b >> l >> r;

            lc.insert_segment(Line(a, b), l, r, lc.L, lc.R, lc.root);
        }

        else
        {
            ll x;
            cin >> x;

            ll ans = lc.query_point(x, lc.L, lc.R, lc.root);
            
            if (ans == -INF) NO;
            else cout << ans << endl;
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