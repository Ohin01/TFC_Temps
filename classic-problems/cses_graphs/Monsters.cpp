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
vpll mv = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

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

ll n, m;
char grid[1005][1005];
bool vis[1005][1005];

bool valid(int x, int y)
{
    if (x < 0 || x > n - 1) return false;
    if (y < 0 || y > m - 1) return false;
    return true;
}

void dfs(int x, int y)
{
    vis[x][y] = true;

    FOR(i, 0, 4)
    {
        int nx = x + mv[i].ff;
        int ny = y + mv[i].ss;

        if (valid(nx, ny) && grid[nx][ny] == '.' && !vis[nx][ny])
        dfs(nx, ny);
    }
}


void solve()
{
    cin >> n >> m;

    FOR(i, 0, n) FOR(j, 0, m) cin >> grid[i][j];

    pll st, en;
    queue<pll> mons;
    vvi mlev(n, vector<int>(m, INT_MAX));
    vvb mvis(n, vb(m));

    FOR(i, 0, n)
    {
        FOR(j, 0, m)
        {
            if (grid[i][j] == 'M') 
            {
                mons.push({i, j});
                mvis[i][j] = true;
                mlev[i][j] = 0;
            }

            if (grid[i][j] == 'A') st = {i, j};
        }
    }

    while (!mons.empty())
    {
        pll t = mons.front();
        mons.pop();
        //cout << t.ff << " " << t.ss << " " << let[t.ff][t.ss] << endl;

        FOR(i, 0, 4)
        {
            ll nx = t.ff + mv[i].ff;
            ll ny = t.ss + mv[i].ss;

            if (valid(nx, ny) && !mvis[nx][ny] && (grid[nx][ny] == '.' || grid[nx][ny] == 'A' || grid[nx][ny] == 'M'))
            {
                mons.push({nx, ny});
                mvis[nx][ny] = true;
                mlev[nx][ny] = mlev[t.ff][t.ss] + 1;
            }
        }
    }

    queue<pll> q;

    q.push(st);

    vector<vector<char>> let(1005, vector<char>(1005, 'X'));
    vvi olev(n, vi(m, INT_MAX));

    olev[st.ff][st.ss] = 0;

    let[st.ff][st.ss] = 'A';

    while (!q.empty())
    {
        pll t = q.front();
        q.pop();
        //cout << t.ff << " " << t.ss << " " << let[t.ff][t.ss] << endl;

        FOR(i, 0, 4)
        {
            ll nx = t.ff + mv[i].ff;
            ll ny = t.ss + mv[i].ss;

            if (valid(nx, ny) && let[nx][ny] == 'X' && (grid[nx][ny] == '.' || grid[nx][ny] == 'M'))
            {
                q.push({nx, ny});
                olev[nx][ny] = olev[t.ff][t.ss] + 1;
                //{0, 1}, {0, -1}, {1, 0}, {-1, 0}
                if (i == 0) let[nx][ny] = 'D';
                if (i == 1) let[nx][ny] = 'U';
                if (i == 2) let[nx][ny] = 'R';
                if (i == 3) let[nx][ny] = 'L'; 
            }
        }
    }

    en.ff = INT_MAX, en.ss = INT_MAX;

    FOR(i, 0, m)
    {
        if (grid[0][i] == 'A' || grid[n - 1][i] == 'A')
        {
            YES;
            cout << 0 << endl;
            return;
        }
        if (olev[0][i] < mlev[0][i] && grid[0][i] == '.') en = {0, i};
        if (olev[n - 1][i] < mlev[n - 1][i] && grid[n - 1][i] == '.') en = {n - 1, i};
    }

    
    FOR(i, 0, n)
    {
        if (grid[i][0] == 'A' || grid[i][m - 1] == 'A')
        {
            YES;
            cout << 0 << endl;
            return;
        }
        if (olev[i][0] < mlev[i][0] && grid[i][0] == '.') en = {i, 0};
        if (olev[i][m - 1] < mlev[i][m - 1] && grid[i][m - 1] == '.') en = {i,  m - 1};
    }

    if (en.ff == INT_MAX && en.ss == INT_MAX) 
    {
        NO;
        return;
    }

    if (let[en.ff][en.ss] != 'X')
    {
        YES;
        ll len = 0;

        if (let[en.ff][en.ss] == 'A')
        {
            cout << 0 << endl;
            return;
        }

        ll px = en.ff, py = en.ss;

        string ans = "";

        while (true)
        {
            ans += let[px][py];
            if (let[px][py] == 'D') px--;
            else if (let[px][py] == 'U') px++;
            else if (let[px][py] == 'R') py--;
            else if (let[px][py] == 'L') py++;
            //cout << px << " " << py << endl;
            len++;

            if (px == st.ff && py == st.ss) break;
        }

        cout << len << endl;

        reverse(ans.begin(), ans.end());

        cout << ans << endl;
    }

    else
    {
        NO;
    }



}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    while (cases--)
    {
        solve();
    }
}