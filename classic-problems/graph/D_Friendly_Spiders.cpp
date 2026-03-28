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
const int MX = 3e5 + 5;

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

vector<int> spf(MX, 1);

void sieve()
{
    spf[0] = 0;

    for (int i = 2; i <= MX; i++) {
        if (spf[i] == 1) { 
            for (int j = i; j <= MX; j += i) {
                if (spf[j]== 1)
                    spf[j] = i;
            }
        }
    }
}

vector<int> getFactorization(int x)
{
    vector<int> ret;
    
    unordered_set<int, custom_hash> s;

    while (x != 1) {
        s.insert(spf[x]);
        x = x / spf[x];
    }

    for (int i: s)
    ret.pb(i);

    return ret;
}


void solve()
{
    ll n;
    cin >> n;
    
    ll a[n + 1];
    
    FOR(i, 1, n + 1)
    {
        cin >> a[i];
    }

    unordered_map<int, vi, custom_hash> graph;

    FOR(i, 1, n + 1)
    {
        vi facts = getFactorization(a[i]);

        FOR(j, 0, facts.size())
        {
            graph[facts[j]].pb(i);
        }
    }

    // for (auto it = graph.begin(); it != graph.end(); it++)
    // {
    //     cout << it->ff << ": "<< endl;

    //     for (auto i: it->ss)
    //     cout << i << " ";

    //     cout << endl;
    // }

    ll s, e;
    cin >> s >> e;

    if (s == e)
    {
        cout << 1 << endl << s << endl;
        return;
    }

    vll level(n + 10, 0);
    vb vis(n + 10, false);
    vb primes(MX, false);
    vll par(n + 10, -1);

    

    queue<int> q;

    q.push(s);

    while (!q.empty())
    {
        ll front = q.front();
        q.pop();
        vis[front] = true;

        vi st = getFactorization(a[front]);

        FOR(i, 0, st.size())
        {
            if (primes[st[i]])
            continue;

            primes[st[i]] = true;

            for (auto child: graph[st[i]])
            {
                if (vis[child])
                continue;

                vis[child] = true;
                level[child] = level[front] + 1;
                par[child] = front;
                q.push(child);
            }
        }

        // for (auto child: graph[front])
        // {
        //     if (vis[child])
        //     continue;

        //     level[child] = level[front] + 1;
        //     par[child] = front;
        //     q.push(child);
        // }
    }

    if (level[e] == 0)
    cout << -1 << endl;

    else 
    {
        cout << level[e] + 1 << endl;

        vll ans;

        ll node = e;
        
        FOR(i, 0, level[e] + 1)
        {
            ans.pb(node);
            node = par[node];
        }
        
        FORR(i, level[e], 0)
        cout << ans[i] << " ";

        cout << endl;
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    sieve();
    //cin >> cases;

    while (cases--)
    {
        solve();
    }
}