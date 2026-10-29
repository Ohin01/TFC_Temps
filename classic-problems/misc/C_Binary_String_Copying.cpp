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
    int n,m;
    cin >> n >> m;

    string s;
    cin >> s;

    vpi st;

    int start = 0;
    bool inStr = false;

    FOR(i, 0, n)
    {
        if (s[i] == '1' && s[i + 1] == '0')
        {
            st.pb({start + 1, i + 1});
            start = i + 1;
        }

        else
        {
            continue;
        }
    }

    st.pb({start + 1, n});

    // FOR(i, 0, st.size())
    // cout << st[i].ff << " " << st[i].ss << endl;

    ll ans = 0;

    vpi q;

    while (m--)
    {
        int x, y;
        cin >> x >> y;
        
        q.pb({x, y});
    }

    sort(q.begin(), q.end());

    // cout << endl;
    // FOR(i, 0, q.size())
    // cout << q[i].ff << " " << q[i].ss << endl;

    int mx = -1;

    FOR(i, 0, q.size())
    {
        pi toFind = {q[i].ff, q[i].ss};

        auto it = lower_bound(st.begin(), st.end(), toFind);

        if (it == st.end())
        it--;

        if (it->ff != q[i].ff)
        it--;

        if (q[i].ff >= it->ff && q[i].ss <= it->ss)
        {
            if (ans == 0)
            ans++;

            else
            continue;
        }

        else
        {
            // if (q[i].ss > mx)
            // {
            //     ans++;
            //     mx = q[i].ss;
            // }
            ans++;
        }
    }

    cout << ans << endl;
}

void solve2()
{
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    vll one;
    vll zero;

    FOR(i, 0, n)
    {
        if (s[i] == '1')
        one.pb(i + 1);

        else
        {
            zero.pb((n + 1) - (i + 1));
        }
    }

    // FOR(i, 0, zero.size())
    // cout << zero[i] << " ";
    // cout << endl;

    sort(zero.begin(), zero.end());

    set<pi> ans;

    while (m--)
    {
        int x, y;
        cin >> x >> y;

        //cout << "m  hi" << endl;

        auto it1 = lower_bound(one.begin(), one.end(), x);

        if (it1 == one.end())
        {
            ans.insert({0, 0});
            continue;
        }

        //cout << *it1 << endl;

        if (*it1 > y)
        {
            ans.insert({0, 0});
            //cout << "s" << endl;
            continue;
        }

        auto it2 = lower_bound(zero.begin(), zero.end(), (n + 1) - y);

        if (it2 == zero.end())
        {
            ans.insert({0, 0});
            //cout << "sr" << endl;
            continue;
        }

        //cout << *it2 << endl;

        if ((n + 1) - *it2 < *it1)
        {
            ans.insert({0, 0});
            continue;
        }

        ans.insert({*it1, (n + 1) - *it2});
    }

    cout << ans.size() << endl;
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
        solve2();
    }
}