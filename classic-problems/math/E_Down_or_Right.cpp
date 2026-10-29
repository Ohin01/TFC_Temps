#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename dataType>
using ordered_set = tree<dataType, null_type, less<dataType>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename dataType1, typename dataType2>
using ordered_map = tree<dataType1, dataType2, less<dataType1>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename dataType>
using ordered_multiset = tree<dataType, null_type, less_equal<dataType>, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    template <typename T, typename U>
    size_t operator()(const pair<T, U> &x) const
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();

        uint64_t h1 = splitmix64((uint64_t)x.first + FIXED_RANDOM);
        uint64_t h2 = splitmix64((uint64_t)x.second + FIXED_RANDOM);

        return h1 ^ (h2 >> 1);
    }
};

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;

#define pb push_back
#define ff first
#define ss second
#define index find_by_order
#define FOR(i, a, b) for (ll i = (a); i < (b); i++)
#define FORR(i, a, b) for (ll i = (a); i >= (b); i--)
#define YES cout << "YES\n"
#define NO cout << "NO\n"
#define lcm(a, b) ((a / __gcd(a, b)) * b)

const ll MOD = 1e9 + 7; // 998244353;
const ll INF = 9e18;
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 20;
const ld PI = acos((ld)-1);

ll fact[MX];
ll inv[MX];
vpll mv = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

ll Bigmod(ll a, ll b, ll m)
{
    if (b == 0)
        return 1 % m;
    ll x = Bigmod(a, b / 2LL, m);
    x = (x * x) % m;
    if (b % 2 == 1)
        x = (x * a) % m;
    return x;
}

void pre()
{
    fact[0] = 1;
    inv[0] = 1;
    for (int i = 1; i < MX; i++)
        fact[i] = (i * fact[i - 1]) % MOD;
    inv[MX - 1] = Bigmod(fact[MX - 1], MOD - 2LL, MOD);
    for (int i = MX - 2; i >= 0; i--)
        inv[i] = (inv[i + 1] * (i + 1LL)) % MOD;
}

ll nCr(ll n, ll r, ll p)
{
    if (r > n || r < 0)
        return 0;
    if (n == r || r == 0)
        return 1;
    return (((fact[n] * inv[r]) % p) * inv[n - r]) % p;
}

void ask(ll r1, ll c1, ll r2, ll c2)
{
    if (r1 > r2 || c1 > c2)
    {
        swap(r1, r2);
        swap(c1, c2);
    }
    cout << "? " << r1 << " " << c1 << " " << r2 << " " << c2 << endl;
    cout.flush();
}

bool take()
{
    string s;
    cin >> s;

    if (s == "YES")
        return true;
    else
        return false;
}

ll n;

bool valid(int x, int y)
{
    if (x < 1 || x > n)
        return false;
    if (y < 1 || y > n)
        return false;

    return true;
}

string findPathDP(vector<vector<bool>>& grid) 
{
    vector<vector<bool>> can_reach(n + 2, vector<bool>(n + 2, false));

    can_reach[n][n] = true;

    for (int r = n; r >= 1; r--) 
    {
        for (int c = n; c >= 1; c--) 
        {
            if (r == n && c == n) continue;
            if (!grid[r][c]) 
            {
                can_reach[r][c] = false;
                continue;
            }
            can_reach[r][c] = can_reach[r + 1][c] | can_reach[r][c + 1];
        }
    }

    string path = "";
    int r = 1, c = 1;
    while (r != n || c != n) 
    {
        if (c + 1 <= n && can_reach[r][c + 1]) 
        {
            path += 'R';
            c++;
        } 
        else 
        {
            path += 'D';
            r++;
        }
    }

    return path;
}

void findPath(ll srcx, ll srcy, ll x, ll y, vector<vector<bool>> &grid, vpll &mov)
{
    queue<pll> q;
    q.push({x, y});

    vector<vector<bool>> vis(n + 10, vb(n + 10, false));
    vis[x][y] = true;
    vis[n + 1 - srcx][n + 1 - srcy] = true;

    while (!q.empty())
    {
        pll p = q.front();
        q.pop();
        int cx = p.ff;
        int cy = p.ss;

        if (cx == (n + 1 - srcx) && cy == (n + 1 - srcy))
            break;

        for (auto &m : mov)
        {
            int nx = cx + m.ff;
            int ny = cy + m.ss;

            if (valid(nx, ny) && !vis[nx][ny])
            {
                ask(srcx, srcy, nx, ny);
                vis[nx][ny] = true;
                if (take())
                {
                    grid[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
    }
}

void solve()
{
    cin >> n;

    vector<vector<bool>> grid(n + 10, vb(n + 10, false));
    grid[1][1] = true;
    grid[n][n] = true;

    ll x = -1, y = -1;

    FOR(i, 1, n + 1)
    {
        ask(1, 1, i, n + 1 - i);
        if (take())
        {
            ask(n, n, i, n + 1 - i);
            if (take())
            {
                grid[i][n + 1 - i] = true;
                x = i, y = n + 1 - i;
                break;
            }
        }
    }

    vpll down = {{0, 1}, {1, 0}};
    vpll up = {{0, -1}, {-1, 0}};

    findPath(1, 1, x, y, grid, down);
    findPath(n, n, x, y, grid, up);

    string ans = findPathDP(grid);

    cout << "! " << ans << endl;
    cout.flush();
    return;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int cases = 1;
    // cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        // cout << "Case " << i << ": ";
        solve();
    }
}