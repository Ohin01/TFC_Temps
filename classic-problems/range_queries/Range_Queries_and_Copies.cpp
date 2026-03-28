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
const int LOGN = 20;

ll Bigmod(ll a, ll b, ll m){
    if(b == 0) return 1 % m;
    ll x = Bigmod(a, b / 2LL, m);
    x = (x * x) % m;
    if(b % 2 == 1) x = (x * a) % m;
    return x;
}

struct Node
{
    int left = 0;
    int right = 0;
    ll val = 0;
};

Node nodes[MAX * 40];

struct PerSegTree
{
    int id = 0;

    int build(vll &a, int lx, int rx)
    {
        int cur = ++id;

        if (lx == rx)
        {
            nodes[cur].val = a[lx];
            return cur;
        }

        int mid = (lx + rx) / 2;

        nodes[cur].left = build(a, lx, mid);
        nodes[cur].right = build(a, mid + 1, rx);

        nodes[cur].val = nodes[nodes[cur].left].val + nodes[nodes[cur].right].val;

        return cur;
    }

    int update(int prev, int i, ll v, int lx, int rx)
    {
        int cur = ++id;

        nodes[cur] = nodes[prev];

        if (lx == rx)
        {
            nodes[cur].val = v;
            return cur;
        }

        int mid = (lx + rx) / 2;

        if (i <= mid) 
            nodes[cur].left = update(nodes[cur].left, i, v, lx, mid);
        else
            nodes[cur].right = update(nodes[cur].right, i, v, mid + 1, rx);

        nodes[cur].val = nodes[nodes[cur].left].val + nodes[nodes[cur].right].val;
        return cur;
    }

    ll getSum(int cur, int l, int r, int lx, int rx)
    {
        if (rx < l || r < lx)
        {
            return 0;
        }

        if (lx >= l && rx <= r)
        {
            return nodes[cur].val;
        }

        int mid = (lx + rx) / 2;

        return getSum(nodes[cur].left, l, r, lx, mid) + getSum(nodes[cur].right, l, r, mid + 1, rx);
    }

    ll kth(int u, int v, int k, int lx, int rx, vector<ll> &sortedA) //0-based
    {
        if(lx == rx) return sortedA[lx];

        int mid = (lx + rx) / 2;

        int cnt = nodes[nodes[v].left].val - nodes[nodes[u].left].val;

        if(k <= cnt) 
            return kth(nodes[u].left, nodes[v].left, k, lx, mid, sortedA);
        else
            return kth(nodes[u].right, nodes[v].right, k - cnt, mid + 1, rx, sortedA);
    }
};

void solve()
{
    ll n, q;
    cin >> n >> q;

    vll a(n);

    FOR(i, 0, n) cin >> a[i];

    PerSegTree pst;
    int r = pst.build(a, 0, n - 1);

    vvll roots;

    roots.pb({r});

    int cnt = 1;

    while (q--)
    {
        int t;
        cin >> t;

        if (t == 1)
        {
            ll k, a, x;
            cin >> k >> a >> x;

            k--;
            a--;

            roots[k].pb(pst.update(roots[k][roots[k].size() - 1], a, x, 0, n - 1));
        }

        else if (t == 2)
        {
            ll k, a, b;
            cin >> k >> a >> b;

            k--, a--, b--;

            cout << pst.getSum(roots[k][roots[k].size() - 1], a, b, 0, n - 1) << endl;
        }

        else
        {
            int k;
            cin >> k;

            k--;
            ll lst = roots[k][roots[k].size() - 1];
            //cout << lst << endl;

            ll rr = pst.update(lst, 0, 0, 0, n - 1);
            //cout << rr << endl;

            roots.pb({pst.update(lst, 0, pst.getSum(lst, 0, 0, 0, n - 1), 0, n - 1)});
            //cout << roots[1][0] << endl;
        }
    }

//     Set the value a in array k to x.
// Calculate the sum of values in range [a,b] in array k.
// Create a copy of array k and add it to the end of the list.


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