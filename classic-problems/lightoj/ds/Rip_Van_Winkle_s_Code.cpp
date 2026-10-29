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
const ll INF = 9e15;
const ld PI = acos((ld) -1);
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 20;
 
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
 
struct SegTree
{
    ll sz;
    vll res;
    vpll lazy, lazy2;
    vll lazy3;
    ll dummy;
 
    void init(int n, ll d)
    {
        dummy = d;
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, d);
        lazy.assign(sz * 2, {0LL, 0LL});
        lazy2.assign(sz * 2, {0LL, 0LL});
        lazy3.assign(sz * 2, INF);
    }
 
    ll operation(ll a, ll b)
    {
        return a + b;
    }
 
    void push(int x, int lx, int rx)
    {
        if (lazy[x] == make_pair(0LL, 0LL)) return;
 
        ll len = rx - lx + 1;
        ll l = lx + 1 - lazy[x].ff;
 
        res[x] += (len * lazy[x].ff) + (len - 1) * len / 2 * lazy[x].ss;
 
        if (lx != rx)
        {
            ll mid = (lx + rx) / 2;
 
            lazy[2 * x + 1].ff += (lx - l + 1);
            lazy[2 * x + 1].ss += lazy[x].ss;
 
            //lazy[2 * x + 2].ff += ((mid + 1) - l + 1);
            lazy[2 * x + 2].ff += (lazy[x].ff + (mid - lx + 1) * lazy[x].ss);
            lazy[2 * x + 2].ss += lazy[x].ss;
        }
 
        lazy[x] = {0LL, 0LL};
    }

    void push2(int x, int lx, int rx)
    {
        if (lazy2[x] == make_pair(0LL, 0LL)) return;
 
        ll len = rx - lx + 1;
 
        res[x] += (len * lazy2[x].ff) - (len - 1) * len / 2 * lazy2[x].ss;
 
        if (lx != rx)
        {
            ll mid = (lx + rx) / 2;
 
            lazy2[2 * x + 1].ff += lazy2[x].ff;
            lazy2[2 * x + 1].ss += lazy2[x].ss;
 
            //lazy[2 * x + 2].ff += ((mid + 1) - l + 1);
            lazy2[2 * x + 2].ff += (lazy2[x].ff - (mid - lx + 1) * lazy2[x].ss);
            lazy2[2 * x + 2].ss += lazy2[x].ss;
        }
 
        lazy2[x] = {0LL, 0LL};
    }

    void push3(int x, int lx, int rx)
    {
        if (lazy3[x] == INF) return;

        res[x] = (rx - lx + 1) * lazy3[x];

        if (lx != rx)
        {
            lazy3[2 * x + 1] = lazy3[x];
            lazy3[2 * x + 2] = lazy3[x];

            lazy[2 * x + 1] = {0LL, 0LL};
            lazy[2 * x + 2] = {0LL, 0LL};

            lazy2[2 * x + 1] = {0LL, 0LL};
            lazy2[2 * x + 2] = {0LL, 0LL};
        }

        lazy3[x] = INF;

    }
 
    void build(vll &a, int x, int lx, int rx)
    {
        lazy[x] = {0LL, 0LL};
 
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
 
        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
    }
 
    void update(int l, int r, ll v, int x, int lx, int rx)
    {
        prop(x, lx, rx);
 
        if (r < lx || rx < l) return;
 
        if (lx >= l && rx <= r)
        {
            lazy[x] = {lx - l + 1, 1};
            prop(x, lx, rx);
            return;
        }
 
        ll mid = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, mid);
        update(l, r, v, 2 * x + 2, mid + 1, rx);
 
        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
    }

    void update2(int l, int r, ll v, int x, int lx, int rx)
    {
        prop(x, lx, rx);
 
        if (r < lx || rx < l) return;
 
        if (lx >= l && rx <= r)
        {
            lazy2[x] = {r - lx + 1, 1};
            prop(x, lx, rx);
            return;
        }
 
        ll mid = (lx + rx) / 2;
        update2(l, r, v, 2 * x + 1, lx, mid);
        update2(l, r, v, 2 * x + 2, mid + 1, rx);
 
        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
    }

    void update3(int l, int r, ll v, int x, int lx, int rx)
    {
        prop(x, lx, rx);

        if (r < lx || rx < l) return;

        if (lx >= l && rx <= r)
        {
            lazy3[x] = v;
            prop(x, lx, rx);
            return;
        }

        ll mid = (lx + rx) / 2;
        update3(l, r, v, 2 * x + 1, lx, mid);
        update3(l, r, v, 2 * x + 2, mid + 1, rx);

        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
    }
 
    ll getRes(int l, int r, int x, int lx, int rx)
    {
        prop(x, lx, rx);
        
        if (r < lx || rx < l) 
        {
            return dummy;
        }
 
        if (lx >= l && rx <= r)
        {
            return res[x];
        }
 
        ll mid = (lx + rx) / 2;
 
        return operation(getRes(l, r, 2 * x + 1, lx, mid), getRes(l, r, 2 * x + 2, mid + 1, rx));
    }

    void prop(int x, int lx, int rx)
    {
        push3(x, lx, rx);
        push(x, lx, rx);
        push2(x, lx, rx);
    }
};
 
void solve()
{
    ll n = 250001;
 
    vll a(n);

    SegTree st;
    st.init(n, 0);
    st.build(a, 0, 0, st.sz - 1);

    ll q;
    cin >> q;
 
    while (q--)
    {
        char t;
        cin >> t;
 
        if (t == 'A')
        {           
            ll l, r;
            cin >> l >> r;
 
            l--, r--;
 
            st.update(l, r, 0, 0, 0, st.sz - 1);
        }

        else if (t == 'B')
        {           
            ll l, r;
            cin >> l >> r;
 
            l--, r--;
 
            st.update2(l, r, 0, 0, 0, st.sz - 1);
        }

        else if (t == 'S')
        {           
            ll l, r;
            cin >> l >> r;
 
            l--, r--;
 
            cout << st.getRes(l, r, 0, 0, st.sz - 1) << endl;
        }
 
        else
        {
            ll l, r, v;
            cin >> l >> r >> v;
 
            l--, r--;
 
            st.update3(l, r, v, 0, 0, st.sz - 1);
        }

        //FOR(i, 0, 11) cout << st.getRes(i, i, 0, 0, st.sz - 1) << " "; cout << endl;
    }
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
        cout << "Case " << i << ": " << endl;;
        solve();
    }
}