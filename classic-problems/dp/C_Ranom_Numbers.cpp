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

ll score[] = {1, 10, 100, 1000, 10000};
string s;

ll find(vll &cur, vll &cmp)
{
    ll ans = 0;

    FOR(i, 0, 5)
    {
        ans += cur[i] * score[i];
    }

    FOR(i, 0, 5)
    {
        bool pos = false;

        FOR(j, i + 1, 5)
        {
            if (cmp[j] > 0) pos = true;
        }

        if (pos)
        ans += (-1) * (cur[i]) * score[i];

        else
        ans += cur[i] * score[i];
    }

    return ans;
}

void update(int i, vvll &dep, vvll &inds)
{
    ll let = s[i] - 'A';

    ll req = INF;

    FOR(j, let + 1, 5)
    {
        if (inds[j].size() > 0)
        {
            req = min(req, inds[j][inds[j].size() - 1]);
        }
    }

    if (req != INF) dep[req][let]++;
}

void solve2()
{
    cin >> s;

    ll n = s.size();

    s = '#' + s;

    vvll pref(n + 2, vll(5));
    vvll suf(n + 2, vll(5));
    vvll dep(n + 2, vll(5));
    vvll inds(5);
    ll ans = 0;

    FOR(i, 1, n + 1)
    {
        pref[i][s[i] - 'A'] = pref[i - 1][s[i] - 'A'] + 1;
    }

    //s[4] = 'E';

    FORR(i, n, 1)
    {
        ll let = s[i] - 'A';

        bool plus = true;

        FOR(j, let + 1, 5)
        {
            if (inds[j].size() > 0) plus = false;
        }

        if (plus) ans += score[let];
        else ans -= score[let];

        //plus? cout << score[let] << " " : cout << (-1) * score[let] << " ";

        update(i, dep, inds);

        inds[s[i] - 'A'].pb(i);
        //suf[i][s[i] - 'A'] = pref[i + 1][s[i] - 'A'] + 1;
    }
    //cout << endl;

    // FORR(i, n, 1)
    // {
    //     cout << i << endl;
    //     FOR(j, 0, 5) cout << dep[i][j] << " ";
    //     cout << endl << endl;
    // }

    ll res = ans;
    //cout << res << endl;

    FORR(i, n, 1)
    {
        ll let = s[i] - 'A';

        ll sufx = 0;

        FORR(j, let - 1, 0)
        {
            ll temp = ans + 2 * score[j] * dep[i][j] + sufx;

            sufx += 2 * score[j] * dep[i][j];
            temp -= abs(score[let] - score[j]);

            res = max(res, temp);
        }
    }

    FOR(i, 1, n + 1)
    {
        ll let = s[i] - 'A';

        ll temp = 0;

        FOR(j, let, 4)
        {
            temp -= 2 * score[j] * pref[i - 1][j];
        }

        temp = ans + abs(score[4] + score[let]) - temp;

        res = max(res, temp);
    }


    // FOR(i, 1, n + 1)
    // {
    //     if (s[i] != 'E')
    //     {
    //         res = max(res, ans + score[4] + score[s[i] - 'A']);
    //         break;
    //     }
    // }

    cout << res << endl;
}

ll dp[MAX][5][2];

void solve()
{
    string s;
    cin >> s;

    ll n = s.size();

    FOR(i, 0, n + 1)
    {
        FOR(j, 0, 5)
        {
            FOR(k, 0, 2)
            dp[i][j][k] = -INF;
        }
    }

    FOR(j, 0, 5)
    {
        ll let = s[n - 1] - 'A';

        if (let == j)
        {
            dp[n - 1][j][0] = score[j];
        }

        dp[n - 1][j][1] = score[j];
    }

    FORR(i, n - 2, 0)
    {
        ll let = s[i] - 'A';

        FOR(j, 0, 5)
        {
            FOR(k, 0, 2)
            {
                if (dp[i + 1][j][k] != -INF)
                {
                    if (j > let) dp[i][j][k] = max(dp[i][j][k], dp[i + 1][j][k] - score[let]);

                    else dp[i][let][k] = max(dp[i][let][k], dp[i + 1][j][k] + score[let]);
                }
            }

            FOR(sm, 0, j + 1)
            {
                if (dp[i + 1][sm][0] != -INF)
                dp[i][j][1] = max(dp[i][j][1], dp[i + 1][sm][0] + score[j]);
            }
        }
    }

    ll ans = -INF;

    FOR(j, 0, 5)
    {
        FOR(k, 0, 2)
        {
            ans = max(ans, dp[0][j][k]);
        }
    }

    cout << ans << endl;
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