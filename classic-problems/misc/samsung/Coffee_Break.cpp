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
    string s;
    cin >> s;

    int val = ((s[0] - '0')*10 + (s[1] - '0')) * 60 + (s[3] - '0')*10 + (s[4] - '0');
    
    int cap1 = 0;
    int cap2 = (('1' - '0')*10 + ('1' - '0')) * 60 + ('1' - '0')*10 + ('1' - '0');
    int cap3 = (('2' - '0')*10 + ('2' - '0')) * 60 + ('2' - '0')*10 + ('2' - '0');

    if (val <= cap1)
    cout << "00:00" << endl;

    else if (val <= cap2)
    cout << "11:11" << endl;

    else if (val <= cap3)
    cout << "22:22" << endl;

    else
    cout <<"00:00" << endl;

    return;

    char mx = s[0];

    mx = max(s[1], mx);
    mx = max(s[3], mx);
    mx = max(s[4], mx);

    if (s[0] == '0')
    {
        if (mx == '0')
        cout << "00:00" << endl;

        else
        cout << "11:11" << endl;
    }

    
    if (s[0] == '1')
    {
        if (s[1] == '0')
        cout << "11:11" << endl;

        else if (s[1] == '1')
        {
            int val = (s[3] - '0')*10 + (s[4] - '0');

            if (val <= 11)
            cout << "11:11" << endl;

            else
            cout << "22:22" << endl;
        }

        else
        cout << "22:22" << endl;
    }

    
    if (s[0] == '2')
    {
        if (s[1] <= '1')
        cout << "22:22" << endl;

        else if (s[2] == '2')
        {
            int val = (s[3] - '0')*10 + (s[4] - '0');

            if (val <= 22)
            cout << "22:22" << endl;

            else
            cout << "00:00" << endl;
        }

        else
        cout << "00:00" << endl;
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
        solve();
    }
}