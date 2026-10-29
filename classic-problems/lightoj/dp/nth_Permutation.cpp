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

typedef unsigned long long       ll;
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
const int MX = 21;
const int LOGN = 20;
const ld PI = acos((ld) -1);

ll fact[MX];

void pre() {
    fact[0] = 1;
    for (int i = 1; i < MX; i++) fact[i] = (i * fact[i - 1]);
}

vector<ll> all(26);
int tot;
ll sz;

void func(ll ind, ll perm)
{
    if (ind <= 0)
    {
        cout << endl;
        return;
    }

    ll cnt = fact[ind];
    ll lst = 0;

    FOR(i, 0, 26)
    {
        cnt /= fact[all[i]];
    }

    FOR(i, 0, 26)
    {
        if (all[i] != 0)
        {
            ll ans = cnt * all[i] / ind + lst;

            if (ans >= perm)
            {
                all[i]--;
                cout << (char)(i + 'a');

                //cout << " " << cnt << " " << ind << " " << perm << " " << lst << " " << ans << endl;

                func(ind - 1, perm - lst);
                return;
            }

            lst = ans;
        }
    }

    //ll ans = cnt * fact[all[i]] * fact[ind - 1] / fact[ind] / fact[all[i] - 1] + lst;

}

void solve()
{
    string s;
    cin >> s;

    ll n;
    cin >> n;

    FOR(i, 0, 26) all[i] = 0;

    FOR(i, 0, s.size()) all[s[i] - 'a']++;

    tot = 0;
    sz = s.size();

    ll mot = fact[sz];

    FOR(i, 0, 26) mot /= fact[all[i]];

    if (n > mot) {
        cout << "Impossible" << endl;
        return;
    }

    func(sz, n);
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;
    
    pre();

    for (int i = 1; i <= cases; i++)
    {
        cout << "Case " << i << ": ";
        solve();
    }
}