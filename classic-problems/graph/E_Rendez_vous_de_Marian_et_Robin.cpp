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

void solve()
{
    ll n, m, k;
    cin >> n >> m >> k;

    vll h(k);

    vb horse(n + 1, false);

    FOR(i, 0, k)
    {
        ll num;
        cin >> num;

        horse[num] = true;
    }

    vector<vector<pair<ll, ll>>> graph(n + 1);

    FOR(i, 0, m)
    {
        ll n1, n2, w;
        cin >> n1 >> n2 >> w;

        graph[n1].pb({n2, w});
        graph[n2].pb({n1, w});
    }

    vvll dist1(n + 1, vll(2, INF)), dist2(n + 1, vll(2, INF));

    set<pair<ll, pair<ll, pair<bool, bool>>>> q1, q2;

    q1.insert({0, {1, {false, false}}}); dist1[1][0] = 0;
    q2.insert({0, {n, {false, false}}}); dist2[n][0] = 0;

    vvb vis1(n + 1, vb(2, false)), vis2(n + 1, vb(2, false));

    while (!q1.empty())
    {
        pair<ll, pair<ll, pair<bool, bool>>> front = *q1.begin();
        q1.erase(q1.begin());

        ll node = front.ss.ff;
        ll wt = front.ff;
        bool prev = front.ss.ss.ss;
        bool onhorse = front.ss.ss.ff;

        int prevst = prev? 1:0;

        int state = onhorse? 1:0;

        vis1[node][prevst] = true;

        for (auto child: graph[node])
        {
            //if (vis1[child.ff])
            //continue;

            ll newstate = 0;

            ll chnode = child.ff;
            ll chwt = child.ss;

            if (onhorse || horse[node])
            {
                onhorse = true;
                chwt /= 2;
                newstate = 1;
            }

            if (dist1[node][state] + chwt < dist1[chnode][newstate])
            {
                dist1[chnode][newstate] = min(dist1[chnode][newstate], dist1[node][state] + chwt);
                bool neww = state == 0? false : true;

                if (!vis1[chnode][newstate])
                q1.insert({dist1[chnode][newstate], {chnode, {onhorse, neww}}});
            }

            
        }
    }

    while (!q2.empty())
    {
        pair<ll, pair<ll, pair<bool, bool>>> front = *q2.begin();
        q2.erase(q2.begin());

        ll node = front.ss.ff;
        ll wt = front.ff;
        bool prev = front.ss.ss.ss;
        bool onhorse = front.ss.ss.ff;

        int prevst = prev? 1:0;

        int state = onhorse? 1:0;

        vis2[node][prevst] = true;

        for (auto child: graph[node])
        {
            //if (vis2[child.ff])
            //continue;

            ll newstate = 0;

            ll chnode = child.ff;
            ll chwt = child.ss;

            if (onhorse || horse[node])
            {
                onhorse = true;
                chwt /= 2;
                newstate = 1;
            }

            if (dist2[node][state] + chwt < dist2[chnode][newstate])
            {
                dist2[chnode][newstate] = min(dist2[chnode][newstate], dist2[node][state] + chwt);

                bool neww = state ==0? false:true;

                if (!vis2[chnode][newstate])
                q2.insert({dist2[chnode][newstate], {chnode, {onhorse, neww}}});
            }
        }
    }

    // FOR(i, 1, n + 1)
    // {
    //     cout << dist1[i][0] << " " << dist1[i][1] << endl;
    //     cout << dist2[i][0] << " " << dist2[i][1] << endl;
    //     cout << endl; 
    // }
    // cout << endl;

    ll ans = INF;
    
    FOR(i, 1, n + 1)
    {
        ll res = max(min(dist1[i][0], dist1[i][1]), min(dist2[i][0], dist2[i][1]));

        ans = min(ans, res);
    }

    if (ans == INF)
    cout << -1 << endl;

    else
    cout << ans << endl;


}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    while (cases--)
    {
        solve();
    }
}