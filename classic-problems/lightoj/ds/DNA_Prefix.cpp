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

struct Trie {
    static const int ALPH = 5; // lowercase letters a-z
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

    Trie() 
    {
        root = new Node();
    }

    // Insert a string into trie
    void insert(const string& s) 
    {
        Node* cur = root;
        cur->sz++;
        for (char c : s) {
            int idx = c - 'A';
            if (!cur->nxt[idx]) cur->nxt[idx] = new Node();
            cur = cur->nxt[idx];
            cur->sz++;
        }
        cur->ends_here++;
    }

    // Count exact occurrences of a string
    int search(const string& s) 
    {
        Node* cur = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!cur->nxt[idx]) return 0;
            cur = cur->nxt[idx];
        }
        return cur->ends_here;
    }

    // Count number of strings with given prefix
    int count_prefix(const string& prefix) 
    {
        Node* cur = root;
        for (char c : prefix) 
        {
            int idx = c - 'a';
            if (!cur->nxt[idx]) return 0;
            cur = cur->nxt[idx];
        }
        return cur->sz;
    }

    ll maxCount(string &s)
    {
        Node *cur = root;
        ll ans = 1;

        for (int i = 0; i < s.size(); i++)
        {
            char c = s[i];
            int idx = c - 'A';
            if (!cur->nxt[idx]) return ans;
            cur = cur->nxt[idx];
            ans = max(ans, (ll)(i + 1) * cur->sz);
        }
        return ans;
    }

    // Erase a string (assumes it exists)
    void erase(const string& s) {
        Node* cur = root;
        cur->sz--;
        for (char c : s) {
            int idx = c - 'a';
            cur = cur->nxt[idx];
            cur->sz--;
        }
        cur->ends_here--;
    }

    // Delete all nodes (destructor)
    void del(Node* cur) {
        for (int i = 0; i < ALPH; i++) if (cur->nxt[i]) del(cur->nxt[i]);
        delete cur;
    }

    ~Trie() {
        del(root);
    }
};

void solve()
{
    ll n;
    cin >> n;

    vector<string> vec(n);
    Trie tr;

    FOR(i, 0, n)
    {
        cin >> vec[i];

        FOR(j, 0, vec[i].size())
        {
            if (vec[i][j] == 'C') vec[i][j] = 'B';
            else if (vec[i][j] == 'G') vec[i][j] = 'C';
            else if (vec[i][j] == 'T') vec[i][j] = 'D';
        }

        //cout << vec[i] << endl;

        tr.insert(vec[i]);
    }

    ll ans = 1;

    FOR(i, 0, n)
    {
        ans = max(ans, tr.maxCount(vec[i]));
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

    for (int i = 1; i <= cases; i++)
    {
        cout << "Case " << i << ": ";
        solve();
    }
}