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
    ll n, x, y;
    cin >> n >> x >> y;

    string s;
    cin >> s;

    s = 'X' + s;

    vll p(n + 1);
    FOR(i, 1, n + 1) cin >> p[i];

    ll tot = 0;

    FOR(i, 1, n + 1) tot += p[i];

    if (tot > x + y)
    {
        NO;
        return;
    }

    ll s1 = 0, s2 = 0;

    FOR(i, 1, n + 1)
    {
        if (s[i] == '0') s1 += (p[i]);
        else s2 += p[i];
    }

    //cout << s1 << " " << s2 << endl;

    if (s1 > x && s2 > y)
    {
        NO;
        return;
    }

    if (s1 <= x && s2 <= y)
    {
        ll ones = 0;

        FOR(i, 1, n + 1) if (s[i] == '1') ones++;

        if (ones == 0)
        {
            if (x - y >= n)
            YES;
            else
            NO;
        }

        else if (ones == n)
        {
            if (y - x >= n)
            YES;

            else
            NO;
        }

        else
        {
            YES;
        }
        return;
    }

    if (s1 <= x && s2 > y)
    {
        ll ones = 0;

        FOR(i, 1, n + 1) if (s[i] == '1') ones++;

        ll ex = 0;

        FOR(i, 1, n + 1)
        {
            if (s[i] == '1') ex += (p[i] - 1) / 2;
        }

        ll neyajabe = 0;

        FOR(i, 1, n + 1)
        {
            if (s[i] == '1')
            {
                if (p[i] % 2 == 0) neyajabe += (p[i] + 1) / 2;
                else neyajabe += (p[i] - 1) / 2;
            }
        }

        if (ex < s2 - y) 
        {
            NO;
            return;
        }

        if (ones == n)
        {
            if ((x - s1) >= (s2 - y) && (x - s1) <= neyajabe) YES;
            else NO;
        }

        else
        {  
            if ((x - s1) >= s2 - y) YES;
            else NO;
        }
    }

    else
    {
        ll ones = 0;

        FOR(i, 1, n + 1) if (s[i] == '1') ones++;

        ll ex = 0;

        FOR(i, 1, n + 1)
        {
            if (s[i] == '0') ex += (p[i] - 1) / 2;
        }

        ll neyajabe = 0;

        FOR(i, 1, n + 1)
        {
            if (s[i] == '0')
            {
                if (p[i] % 2 == 0) neyajabe += (p[i] + 1) / 2;
                else neyajabe += (p[i] - 1) / 2;
            }
        }

        if (ex < s1 - x) 
        {
            NO;
            return;
        }

        if (ones == 0)
        {
            if ((y - s2) <= neyajabe && (y - s2) >= s1 - x) YES;
            else NO;
        }

        else
        {  
            if ((y - s2) >= s1 - x) YES;
            else NO;
        }
    }
}

void solve2()
{
    ll n, x, y;
    cin >> n >> x >> y;

    string s;
    cin >> s;

    s = 'X' + s;

    vll p(n + 1);
    FOR(i, 1, n + 1) cin >> p[i];

    ll tot = 0;

    FOR(i, 1, n + 1) tot += p[i];

    if (tot > x + y)
    {
        NO;
        return;
    }

    ll ones = 0;

    FOR(i, 1, n + 1) if (s[i] == '1') ones++;

    if (ones == 0)
    {
         ll ex = 0;
         ll s1 = 0;

        FOR(i, 1, n + 1)
        {
            if (p[i] % 2 == 1) ex += (p[i] - 1) / 2;
            else ex += (p[i] + 1) / 2;
            s1 += p[i];

        }

        if (s1 <= x)
        {
            if (x - y >= n)
            YES;

            else
            NO;
            return;
        }

        else
        {
            if (x - y >= n && x - y <= ex)
            YES;

            else
            NO;

            return;
        }
    }

    else if (ones == n)
    {
        ll ex = 0;
        ll s2 = 0;

        FOR(i, 1, n + 1)
        {
            if (p[i] % 2 == 1) ex += (p[i] - 1) / 2;
            else ex += (p[i] + 1) / 2;
            s2 += p[i];
        }

        if (s2 <= y)
        {
            if (y - x >= n) YES;
            else NO;
            return;
        }

        else
        {
            if (y - x >= n && y - x <= ex)
            YES;

            else
            NO;

            return;
        }
    }

    ll s1 = 0, s2 = 0;

    FOR(i, 1, n + 1)
    {
        if (s[i] == '0') s1 += (p[i]);
        else s2 += p[i];
    }

    if (s1 > x && s2 > y)
    {
        NO;
        return;
    }

    if (s1 <= x && s2 <= y)
    {
        YES;
        return;
    }

    if (s1 <= x && s2 > y)
    {
        ll ex = 0;

        FOR(i, 1, n + 1)
        {
            if (s[i] == '1') ex += (p[i] - 1) / 2;
        }

        if (ex < s2 - y) 
        {
            NO;
            return;
        }

        if ((x - s1) >= (s2 - y)) YES;
        else NO;
    }

    else
    {
        ll ex = 0;

        FOR(i, 1, n + 1)
        {
            if (s[i] == '0') ex += (p[i] - 1) / 2;
        }

        if (ex < s1 - x) 
        {
            NO;
            return;
        }

        if ((y - s2) >= s1 - x) YES;
        else NO;
        
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    while (cases--)
    {
        solve2();
    }
}