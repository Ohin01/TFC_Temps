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

ll n, m;

ll find(vll &a)
{
    vll left(n + 1, -1), right(n + 1, -1);

    stack<ll> st;

    FOR(i, 1, n + 1)
    {
        right[i] = i;

        while (!st.empty())
        {
            ll ind = st.top();

            if (a[ind] > a[i])
            {
                right[ind] = i;
                st.pop();
            }

            else break;
        }

        st.push(i);
    }

    while (!st.empty()) 
    {
        ll ind = st.top();
        right[ind] = n + 1;
        st.pop();
    }

    FORR(i, n, 1)
    {
        left[i] = i;

        while (!st.empty())
        {
            ll ind = st.top();

            if (a[ind] > a[i])
            {
                left[ind] = i;
                st.pop();
            }

            else break;
        }

        st.push(i);
    }

    while (!st.empty()) 
    {
        ll ind = st.top();
        left[ind] = 0;
        st.pop();
    }

    ll ans = 0;

    FOR(i, 1, n + 1)
    {
        //cout << left[i] << " " << right[i] << endl;
        ans = max(ans, a[i] * (right[i] - left[i] - 1));
    }

    return ans;
}

void solve()
{
    cin >> m >> n;

    vvll grid(m + 1, vll(n + 1)), dp(m + 1, vll(n + 1));

    FOR(i, 1, m + 1)
    {
        FOR(j, 1, n + 1)
        {
            char c;
            cin >> c;

            grid[i][j] = c - '0';
        }
    }

    FORR(i, m, 1)
    {
        if (i == m)
        {
            FOR(j, 1, n + 1) grid[i][j] == 1? dp[i][j] = 0 : dp[i][j] = 1;
        }

        else
        {
            FOR(j, 1, n + 1)
            {
                if (grid[i][j] == 1)
                {
                    dp[i][j] = 0;
                }

                else
                {
                    dp[i][j] = 1 + dp[i + 1][j];
                }
            }
        }
    }

    ll ans = 0;

    FOR(i, 1, m + 1) ans = max(ans, find(dp[i]));

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