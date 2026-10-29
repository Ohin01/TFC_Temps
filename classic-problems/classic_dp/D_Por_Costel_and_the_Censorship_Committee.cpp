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

vector<int> z_function(string s) 
{
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
        z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        ++z[i];
    if (i + z[i] - 1 > r)
        l = i, r = i + z[i] - 1;
    }
    return z;
}

struct SegTree
{
    ll sz = 0;
    vll res;
    vll lazy;
    ll dummy;

    void init(int n, ll d)
    {
        dummy = d;
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, d);
        lazy.assign(sz * 2, -1);
    }

    ll op(ll a, ll b)
    {
        return min(a, b);
    }

    void push(int x, int lx, int rx)
    {
        if (lazy[x] == -1) return;

        res[x] = lazy[x];

        if (lx != rx)
        {
            lazy[2 * x + 1] = lazy[x];
            lazy[2 * x + 2] = lazy[x];
        }

        lazy[x] = -1;
    }

    void build(vll &a, int x, int lx, int rx)
    {
        lazy[x] = -1;

        if (lx == rx)
        {
            if (lx < (int)a.size())
            res[x] = a[lx];

            else
            res[x] = dummy;
            return; 
        }

        ll mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid + 1, rx);

        res[x] = op(res[2 * x + 1], res[2 * x + 2]);
    }

    void update(int l, int r, ll v, int x, int lx, int rx)
    {
        push(x, lx, rx);

        if (r < lx || rx < l) return;

        if (lx >= l && rx <= r)
        {
            lazy[x] = v;
            push(x, lx, rx);
            return;
        }

        ll mid = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, mid);
        update(l, r, v, 2 * x + 2, mid + 1, rx);

        res[x] = op(res[2 * x + 1], res[2 * x + 2]);
    }

    ll getRes(int l, int r, int x, int lx, int rx)
    {
        push(x, lx, rx);
        
        if (r < lx || rx < l) 
        {
            return dummy;
        }

        if (lx >= l && rx <= r)
        {
            return res[x];
        }

        ll mid = (lx + rx) / 2;

        return op(getRes(l, r, 2 * x + 1, lx, mid), getRes(l, r, 2 * x + 2, mid + 1, rx));
    }
};

ll n;
string s;
vll lefts(MX, -1);
vll vals(MX, 0);

static const int ALPH = 26; // lowercase letters a-z
struct Node 
{
    Node* nxt[ALPH];
    int sz;        // number of strings passing through this node
    int ends_here; // number of strings ending at this node
    Node() {
        fill(nxt, nxt + ALPH, nullptr);
        sz = ends_here = 0;
    }
};

Node* root;

// Insert a string into trie
void insert(const string& s) 
{
    Node* cur = root;
    cur->sz++;
    for (char c : s) {
        int idx = c - 'a';
        if (!cur->nxt[idx]) cur->nxt[idx] = new Node();
        cur = cur->nxt[idx];
        cur->sz++;
    }
    cur->ends_here++;
}

int firstForbiddenEnd(int pos)
{
    Node* cur = root;

    for(int r = pos; r < n; r++)
    {
        int idx = s[r] - 'a';

        if(!cur->nxt[idx])
            return -1;

        cur = cur->nxt[idx];

        if(cur->ends_here)
            return r;   // first forbidden word found
    }

    return -1;
}

void fill2(string &a)
{
    string z = a + '$' + s;

    vector<int> tmp = z_function(z);

    FOR(i, a.size(), z.size())
    {
        if (tmp[i] == (ll)a.size())
        {
            ll l = i - a.size();
            ll r = i + tmp[i] - 1 - a.size();

            lefts[r] = max(lefts[r], l);

            //cout << l << " " << r << " " << a << endl;
        }
    }
}

void fill()
{
    for(int l = 0; l < n; l++)
    {
        int r = firstForbiddenEnd(l);

        if(r != -1)
            lefts[r + 1] = max(lefts[r + 1], (ll)(l + 1));
    }
}

void del(Node* cur) {
        for (int i = 0; i < ALPH; i++) if (cur->nxt[i]) del(cur->nxt[i]);
        delete cur;
    }

void solve()
{
    cin >> n;
    cin >> s;

    root = new Node();

    FOR(i, 1, n + 1)
    {
        cin >> vals[i];
        lefts[i] = -1;
    }

    vals[n + 1] = 0;

    ll q;
    cin >> q;

    while(q--)
    {
        string a;
        cin >> a;

        insert(a);
        //fill(a);
    }

    fill();

    //FOR(i, 1, n + 1) cout << lefts[i] << " ";

    SegTree st;
    st.init(n + 10, INF);

    vll dp(n + 10, INF);

    dp[0] = 0;
    st.update(0, 0,  0, 0, 0, st.sz - 1);

    FOR(i, 1, n + 1)
    {
        if (lefts[i] != -1)
        {
            st.update(0, lefts[i] - 1, INF, 0, 0, st.sz - 1);
        }

        dp[i] = st.getRes(0, i - 1, 0, 0, st.sz - 1) + vals[i];
        //cout << i << " " << st.getRes(0, i - 1, 0, 0, st.sz - 1) << endl;
        st.update(i, i, dp[i], 0, 0, st.sz - 1);
    }

    ll ans = INF;

    FOR(i, 1, n + 1) ans = min(ans, st.getRes(i, i, 0, 0, st.sz - 1));
    cout << ans << endl;

    del(root);
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("cenzura.in", "r", stdin);
    freopen("cenzura.out", "w", stdout);
    
    int cases = 1;
    cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}