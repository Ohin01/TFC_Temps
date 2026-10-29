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

struct Trie
{
    static const int B = 31;
    struct Node
    {
        Node* nxt[2];
        int sz;
        Node()
        {
            nxt[0] = nxt[1] = NULL;
            sz = 0;
        }
    };

    Node *root;

    Trie()
    {
        root = new Node();
    }

    void insert(int val)
    {
        Node* cur = root;
        cur->sz++;
        for (int i = B - 1; i >= 0; i--)
        {
            int b = (1LL<<i) & val ? 1 : 0;
            if (cur->nxt[b] == NULL) cur->nxt[b] = new Node();
            cur = cur->nxt[b];
            cur->sz++;
        }
    }

    void erase(int val) //make sure to continue cur->sz == 0 while query
    {
        Node *cur = root;
        cur->sz--;

        for(int i = B - 1; i >= 0; i--)
        {
            int b = (1LL<<i) & val ? 1 : 0;
            cur = cur->nxt[b];
            cur->sz--;
        }
    }

    int query(int x, int k) // number of values s.t. val ^ x < k
    {
        Node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--)
        {
            if (cur == NULL) break;
            int b1 = (1LL<<i) & x ? 1 : 0, b2 = (1LL<<i) & k ? 1 : 0;
            if (b2 == 1)
            {
                if (cur->nxt[b1]) ans += cur->nxt[b1]->sz;
                cur = cur->nxt[!b1];
            }
            else cur = cur->nxt[b1];
        }
        return ans;
    }

    int get_max(int x) // returns maximum of val ^ x
    {
        Node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--)
        {
            int k = (1LL<<i) & x ? 1 : 0;
            if (cur->nxt[!k]) cur = cur->nxt[!k], ans <<= 1, ans++;
            else cur = cur->nxt[k], ans <<= 1;
        }
        return ans;
    }

    int get_min(int x) // returns minimum of val ^ x
    {
        Node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--)
        {
            int k = (1LL<<i) & x ? 1 : 0;
            if (cur->nxt[k]) cur = cur->nxt[k], ans <<= 1;
            else cur = cur->nxt[!k], ans <<= 1, ans++;
        }
        return ans;
    }

    void del(Node* cur)
    {
        for (int i = 0; i < 2; i++) if (cur->nxt[i]) del(cur->nxt[i]);
        delete(cur);
    }
};

void solve()
{
    ll n;
    cin >> n;

    int mn = INT_MAX;
    int mx = -INT_MAX;

    vi a(n);
    FOR(i, 0, n) cin >> a[i];
    //sort(a.begin(), a.end());

    vi pref(n);
    pref[0] = a[0];
    FOR(i, 1, n) pref[i] = pref[i - 1] ^ a[i];

    Trie tr;
    tr.insert(0);

    FOR(i, 0, n)
    {
        mn = min(mn, tr.get_min(pref[i]));
        mx = max(mx, tr.get_max(pref[i]));

        tr.insert(pref[i]);
    }

    cout << mx << " " << mn << endl;

    tr.del(tr.root);
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