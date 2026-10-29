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

ll fact[MX];
ll inv[MX];
vpll mv = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

ll Bigmod(ll a, ll b, ll m){
    if(b == 0) return 1 % m;
    ll x = Bigmod(a, b / 2LL, m);
    x = (x * x) % m;
    if(b % 2 == 1) x = (x * a) % m;
    return x;
}

void pre() {
    fact[0] = 1;
    for (int i = 1; i < MX; i++) fact[i] = (i * fact[i - 1]) % MOD;
    inv[MX - 1] = Bigmod(fact[MX - 1], MOD - 2LL, MOD);
    for (int i = MX - 2; i >= 0; i--) inv[i] = (inv[i + 1] * (i + 1LL)) % MOD;
}

ll nCr(ll n, ll r, ll p) { 
    if(r > n || r < 0) return 0;
    if(n == r || r == 0) return 1;
    return (((fact[n] * inv[r]) % p ) * inv[n - r]) % p;
}

pi mov[52][52][4];
char grid[52][52];
ll dp[52][52][10002];
bool vis[52][52][10002];
int n, m;
string s;

bool valid(int x, int y)
{
    if (x < 1 || x > n) return false;
    if (y < 1 || y > m) return false;

    return true;
}

void fill()
{
    FOR(i, 1, n + 1)
    {
        FOR(j, 1, m + 1)
        {
            char c = grid[i][j];

            mov[i][j][0] = mov[i][j][1] = mov[i][j][2] = mov[i][j][3] = {0, 0};

            FORR(x, i - 1, 1)
            {
                if (grid[x][j] != c)
                {
                    mov[i][j][0] = {x, j};
                    break;
                }
            }

            FOR(x, i + 1, n + 1)
            {
                if (grid[x][j] != c)
                {
                    mov[i][j][2] = {x, j};
                    break;
                }
            }

            FOR(y, j + 1, m + 1)
            {
                if (grid[i][y] != c)
                {
                    mov[i][j][1] = {i, y};
                    break;
                }
            }

            FORR(y, j - 1, 1)
            {
                if (grid[i][y] != c)
                {
                    mov[i][j][3] = {i, y};
                    break;
                }
            }
        }
    }
}

void solve()
{
    cin >> n >> m;
    FOR(i, 1, n + 1)
    {
        FOR(j, 1, m + 1) cin >> grid[i][j];
    }

    string temp;
    cin >> temp;

    ll tot = temp.size() + 1;

    ll ans = tot;

    s = "#";

    FOR(i, 0, temp.size())
    {
        if (temp[i] == s.back()) continue;
        else s += temp[i];
    }

    s += "*";
    ll mot = s.size() - 1;

    FOR(i, 1, n + 1)
    {
        FOR(j, 1, m + 1)
        {
            FOR(ind, 1, mot + 1)
            {
                dp[i][j][ind] = INF;
            }
        }
    }

    fill();

    //cout << mov[2][3][3].ff << " " << mov[2][3][3].ss << endl;

    queue<tuple<int, int, int>> q;
    q.push({1, 1, 1});
    vis[1][1][1] = true;
    dp[1][1][1] = 0;

    while (!q.empty())
    {
        tuple<int, int, int> t = q.front();
        q.pop();
        int x = get<0>(t);
        int y = get<1>(t);
        int ind = get<2>(t);

        int nind = ind;

        //cout << x << " " << y << " " << ind << " " << dp[x][y][ind] << endl;

        if (grid[x][y] == s[ind]) nind++;
        if (nind > mot) continue;

        FOR(i, 0, 4)
        {
            pi p = mov[x][y][i];
            int nx = p.ff;
            int ny = p.ss;

            if (valid(nx, ny) && !vis[nx][ny][nind])
            {
                dp[nx][ny][nind] = dp[x][y][ind] + 1;
                vis[nx][ny][nind] = true;
                q.push({nx, ny, nind});
            }
        }
    }

    ll mn = INF;

    FOR(i, 1, n + 1)
    {
        FOR(j, 1, m + 1)
        {
            if (s.back() == grid[i][j])
            {
                mn = min(mn, (ll)dp[i][j][mot]);
            }
        }
    }

    //cout << s << endl;
    //cout << mn << " " << ans << endl;
    cout << mn + ans << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}