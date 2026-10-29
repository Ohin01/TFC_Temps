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

void solve()
{
    ll n, k;
    cin >> n >> k;
    
    ll a[n];
    ll mx = -1;
    
    FOR(i, 0, n)
    {
        cin >> a[i];
        mx = max(mx, a[i]);
    }

    map<ll, ll> ans;

    FORR(i, n - 1, 0)
    {
        ll sum = 0;
        ll prev = a[i];

        FORR(j, i - 1, 0)
        {
            ll num = a[i] + (i - j);

            if (num < a[j])
            break;

            sum += (prev - a[j] + 1);

            if (sum > k)
            break;

            if (num > mx)
            {
                ans[sum] = max(ans[sum], num);
            }

            prev = num;
        }
    }

    for (auto it = ans.begin(); it != ans.end(); it++)
    {
        cout << it->ff << " " << it->ss << endl;
    }

    if (ans.empty())
    {
        cout << mx << endl;
        return;
    }

    auto it = ans.lower_bound(k);

    if (it == ans.end())
    {
        it--;
        cout << it->ss << endl;
    }

    else
    {
        if (it->ff == k)
        {
            cout << it->ss << endl;
            return;
        }

        if (it == ans.begin())
        {
            cout << mx << endl;
            return;
        }

        it--;
        cout << it->ss << endl;
    }
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