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

struct segTree
{
    ll siz = 0;
    vpll mn;

    void init(int n)
    {
        siz = 1;

        while(siz < n) siz *= 2;
        mn.assign(2 * siz, {INF, 1});
    }

    void build(vll &arr, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < arr.size())
            mn[x] = {arr[lx], 1};
            return;
        }

        int mid = (lx + rx)/ 2;

        build(arr, 2 * x + 1, lx, mid);
        build(arr, 2 * x + 2, mid, rx);

        if (mn[2 * x + 1].ff == mn[2 * x + 2].ff)
        {
            mn[x] = make_pair(mn[2 * x + 1].ff, mn[2* x + 1].ss + mn[2 * x + 2].ss);
        }

        else
        mn[x] = min(mn[2 * x + 1], mn[2 * x + 2]);
    }

    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            mn[x] = {v,1};
            return;
        }

        int mid = (lx + rx) / 2;

        if (i >= lx && i < mid)
        set(i, v, 2 * x + 1, lx, mid);

        else
        set(i, v, 2 * x + 2, mid, rx);

        if (mn[2 * x + 1].ff == mn[2 * x + 2].ff)
        {
            mn[x] = make_pair(mn[2 * x + 1].ff, mn[2*x+ 1].ss + mn[2 * x + 2].ss);
        }

        else
        mn[x] = min(mn[2 * x + 1], mn[2 * x + 2]);
    }

    pll minRange(int l, int r, int x, int lx, int rx)
    {
        if (rx <= l || lx >= r)
        return {INF, 1};

        if (lx >= l && rx <= r)
        return mn[x];

        int mid = (lx + rx) / 2;

        pll left = minRange(l, r, 2 * x + 1, lx, mid);
        pll right = minRange(l, r, 2 * x + 2, mid, rx);

        if (left.ff == right.ff)
        {
            return make_pair(right.ff, left.ss + right.ss);
        }

        else
        return min(left, right);
    }
};

struct segTree2
{
    ll siz = 0;
    vll mn;

    void init(int n)
    {
        siz = 1;

        while(siz < n) siz *= 2;
        mn.assign(2 * siz, 0);
    }

    void build(vll &arr, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < arr.size())
            mn[x] = arr[lx];
            return;
        }

        int mid = (lx + rx)/ 2;

        build(arr, 2 * x + 1, lx, mid);
        build(arr, 2 * x + 2, mid, rx);

        mn[x] = __gcd(mn[2 * x + 1], mn[2 * x + 2]);
    }

    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            mn[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;

        if (i >= lx && i < mid)
        set(i, v, 2 * x + 1, lx, mid);

        else
        set(i, v, 2 * x + 2, mid, rx);

        mn[x] = __gcd(mn[2 * x + 1], mn[2 * x + 2]);
    }

    ll minRange(int l, int r, int x, int lx, int rx)
    {
        if (rx <= l || lx >= r)
        return 0;

        if (lx >= l && rx <= r)
        return mn[x];

        int mid = (lx + rx) / 2;

        return __gcd(minRange(l, r, 2 * x + 1, lx, mid), minRange(l, r, 2 * x + 2, mid, rx));
    }
};

void solve()
{
    ll n;
    cin >> n;

    vll a(n);

    FOR(i, 0, n)
    cin >> a[i];

    int q;
    cin >> q;

    vpll ranges;

    segTree st;
    segTree2 st2;

    st2.init(n);

    st.init(n);

    st.build(a, 0, 0, st.siz);
    st2.build(a, 0, 0, st2.siz);

    // int left = 1;

    // ll mn = a[0];

    // FOR(i, 1, n)
    // {
    //     if (a[i] > mn)
    //     {
    //         if (a[i] % mn == 0)
    //         {
    //             if (i == n - 1)
    //             ranges.pb({left, i + 1});
    //             continue;
    //         }

    //         else
    //         {
    //             ranges.pb({left, i});
    //             left = i + 1;
    //             mn = a[i];
    //         }
    //     }
        
    //     else if (mn > a[i])
    //     {
    //         if (mn % a[i] == 0)
    //         {
    //             mn = a[i];
    //             if (i == n - 1)
    //             ranges.pb({left, i + 1});
    //             continue;
    //         }

    //         else
    //         {
    //             ranges.pb({left, i});
    //             left = i + 1;
    //             mn = a[i];  
    //         }
    //     }

    //     else 
    //     {
    //         if (i == n - 1)
    //             ranges.pb({left, i + 1});
    //             continue;
    //     }
    // }

    // FOR(i, 0, ranges.size())
    // cout << ranges[i].ff << " " << ranges[i].ss << endl;



    while(q--)
    {
        int l, r;
        cin >> l >> r;

        pll p = st.minRange(l - 1, r, 0, 0, st.siz);

        ll val = p.ff;
        ll cnt = p.ss;

        if (val == st2.minRange(l - 1, r, 0, 0, st2.siz))
        {
            cout << (r - l + 1) - cnt << endl;
        }

        else
        {
            cout << (r - l + 1) << endl;
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

    while (cases--)
    {
        solve();
    }
}