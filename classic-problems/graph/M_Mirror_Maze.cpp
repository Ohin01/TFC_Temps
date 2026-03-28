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

ll n, m;

bool valid(ll x, ll y)
{
    if (x < 1 || x > n)
    return false;

    if (y < 1 || y > m)
    return false;

    return true;
}

void solve()
{
    cin >> n >> m;

    ll mirror = 0;

    vector<vector<char>> grid(n + 1, vector<char>(m + 1));
    vvll mirrorid(n + 1, vll(m + 1, 0));

    FOR(i, 1, n + 1)
    {
        FOR(j, 1, m + 1)
        {
            cin >> grid[i][j];

            if (grid[i][j] == '/' || grid[i][j] == '\\' )
            {
                mirrorid[i][j] = mirror;
                mirror++;
            }
        }
    }

    if (mirror == 1)
    {
        cout << 4 << endl;

        FOR(i, 1, n + 1)
        {
            FOR(j, 1, m + 1)
            {
                if (grid[i][j] == '/' || grid[i][j] == '\\' )
                {
                    cout << "S" << j << " " << "N" << j << " " << "E" << i << " " << "W" << i << endl;
                    return;
                }
            }
        }
    }

    vector<string> ans;
    vector<vvb> vis(n + 1, vvb(m + 1, vb(2, false)));

    FOR(i, 1, m + 1)
    {
        unordered_set<ll, custom_hash> allids;
        ll x = 1;
        ll y = 0;
        ll dir = 1;

        ll row = 0;
        ll col = i;

        queue<pll> q;
        q.push({row, col});

        if (grid[row][col] == '\\')
        {
            dir ^= 1;
            
            ll temp = x;
            x = y;
            y = temp;
            allids.insert(mirrorid[row][col]);
        }

        else if (grid[row][col] == '/')
        {
            dir ^= 1;
            
            ll temp = x;
            x = -1 * y;
            y = -1 * temp;
            allids.insert(mirrorid[row][col]);
        }

        else
        vis[row][col][dir] = true;

        ll lastr, lastc;

        while (!q.empty())
        {
            pll top = q.front();
            q.pop();

            ll r = top.ff;
            ll c = top.ss;

            // vis[r][c][dir] = true;

            ll newr = r + x;
            ll newc = c + y;

            lastr = r;
            lastc = c;

            //cout << newr << "  " << newc << endl;

            if (valid(newr, newc) && !vis[newr][newc][dir])
            {
                if (grid[newr][newc] == '\\')
                {
                    dir ^= 1;
                    
                    ll temp = x;
                    x = y;
                    y = temp;
                    allids.insert(mirrorid[newr][newc]);
                }

                else if (grid[newr][newc] == '/')
                {
                    dir ^= 1;
                    
                    ll temp = x;
                    x = -1 * y;
                    y = -1 * temp;
                    allids.insert(mirrorid[newr][newc]);
                }

                else
                vis[newr][newc][dir] = true;
                
                q.push({newr, newc});
            }
        }

        if ((ll)allids.size() == mirror)
        {
            cout << 2 << endl;
            cout << "N" << i << " ";

            if (dir == 0)
            {
                if (lastc == 1)
                cout << "W" << lastr << endl;

                else
                cout << "E" << lastr << endl;
            }

            else
            {
                if (lastr == 1)
                cout << "N" << lastc << endl;

                else
                cout << "S" << lastc << endl;
            }

            return;
        }
    }

    FOR(i, 1, m + 1)
    {
        unordered_set<ll, custom_hash> allids;
        //vector<vvb> vis(n + 1, vvb(m + 1, vb(2, false)));

        ll x = -1;
        ll y = 0;
        ll dir = 1;

        ll row = n;
        ll col = i;

        queue<pll> q;
        q.push({row, col});

        if (grid[row][col] == '\\')
        {
            dir ^= 1;
            
            ll temp = x;
            x = y;
            y = temp;
            allids.insert(mirrorid[row][col]);
        }

        else if (grid[row][col] == '/')
        {
            dir ^= 1;
            
            ll temp = x;
            x = -1 * y;
            y = -1 * temp;
            allids.insert(mirrorid[row][col]);
        }

        else
        vis[row][col][dir] = true;

        ll lastr, lastc;

        while (!q.empty())
        {
            pll top = q.front();
            q.pop();

            ll r = top.ff;
            ll c = top.ss;

            // vis[r][c][dir] = true;

            ll newr = r + x;
            ll newc = c + y;

            lastr = r;
            lastc = c;

            if (valid(newr, newc) && !vis[newr][newc][dir])
            {
                if (grid[newr][newc] == '\\')
                {
                    dir ^= 1;
                    
                    ll temp = x;
                    x = y;
                    y = temp;
                    allids.insert(mirrorid[newr][newc]);
                }

                else if (grid[newr][newc] == '/')
                {
                    dir ^= 1;
                    
                    ll temp = x;
                    x = -1 * y;
                    y = -1 * temp;
                    allids.insert(mirrorid[newr][newc]);
                }

                else
                vis[newr][newc][dir] = true;
                
                q.push({newr, newc});
            }
        }

        if ((ll)allids.size() == mirror)
        {
            cout << 2 << endl;
            cout << "S" << i << " ";

            if (dir == 0)
            {
                if (lastc == 1)
                cout << "W" << lastr << endl;

                else
                cout << "E" << lastr << endl;
            }

            else
            {
                if (lastr == 1)
                cout << "N" << lastc << endl;

                else
                cout << "S" << lastc << endl;
            }

            return;
        }
    }

    FOR(i, 1, n + 1)
    {
        unordered_set<ll, custom_hash> allids;
        //vector<vvb> vis(n + 1, vvb(m + 1, vb(2, false)));

        ll x = 0;
        ll y = 1;
        ll dir = 0;

        ll row = i;
        ll col = 0;

        queue<pll> q;
        q.push({row, col});

        if (grid[row][col] == '\\')
        {
            dir ^= 1;
            
            ll temp = x;
            x = y;
            y = temp;
            allids.insert(mirrorid[row][col]);
        }

        else if (grid[row][col] == '/')
        {
            dir ^= 1;
            
            ll temp = x;
            x = -1 * y;
            y = -1 * temp;
            allids.insert(mirrorid[row][col]);
        }

        else
        vis[row][col][dir] = true;

        ll lastr, lastc;

        while (!q.empty())
        {
            pll top = q.front();
            q.pop();

            ll r = top.ff;
            ll c = top.ss;

            // vis[r][c][dir] = true;

            ll newr = r + x;
            ll newc = c + y;

            lastr = r;
            lastc = c;

            if (valid(newr, newc) && !vis[newr][newc][dir])
            {
                if (grid[newr][newc] == '\\')
                {
                    dir ^= 1;
                    
                    ll temp = x;
                    x = y;
                    y = temp;
                    allids.insert(mirrorid[newr][newc]);
                }

                else if (grid[newr][newc] == '/')
                {
                    dir ^= 1;
                    
                    ll temp = x;
                    x = -1 * y;
                    y = -1 * temp;
                    allids.insert(mirrorid[newr][newc]);
                }

                else
                vis[newr][newc][dir] = true;
                
                q.push({newr, newc});
            }
        }

        if ((ll)allids.size() == mirror)
        {
            cout << 2 << endl;
            cout << "W" << i << " ";

            if (dir == 0)
            {
                if (lastc == 1)
                cout << "W" << lastr << endl;

                else
                cout << "E" << lastr << endl;
            }

            else
            {
                if (lastr == 1)
                cout << "N" << lastc << endl;

                else
                cout << "S" << lastc << endl;
            }

            return;
        }
    }

    FOR(i, 1, n + 1)
    {
        unordered_set<ll, custom_hash> allids;
        //vector<vvb> vis(n + 1, vvb(m + 1, vb(2, false)));

        ll x = 0;
        ll y = -1;
        ll dir = 0;

        ll row = i;
        ll col = m;

        queue<pll> q;
        q.push({row, col});

        if (grid[row][col] == '\\')
        {
            dir ^= 1;
            
            ll temp = x;
            x = y;
            y = temp;
            allids.insert(mirrorid[row][col]);
        }

        else if (grid[row][col] == '/')
        {
            dir ^= 1;
            
            ll temp = x;
            x = -1 * y;
            y = -1 * temp;
            allids.insert(mirrorid[row][col]);
        }

        else
        vis[row][col][dir] = true;

        ll lastr, lastc;


        while (!q.empty())
        {
            pll top = q.front();
            q.pop();

            ll r = top.ff;
            ll c = top.ss;

            // vis[r][c][dir] = true;

            //cout << i << " " << r << " " << c << endl;

            ll newr = r + x;
            ll newc = c + y;

            lastr = r;
            lastc = c;

            if (valid(newr, newc) && !vis[newr][newc][dir])
            {
                if (grid[newr][newc] == '\\')
                {
                    dir ^= 1;
                    
                    ll temp = x;
                    x = y;
                    y = temp;
                    allids.insert(mirrorid[newr][newc]);
                }

                else if (grid[newr][newc] == '/')
                {
                    dir ^= 1;
                    
                    ll temp = x;
                    x = -1 * y;
                    y = -1 * temp;
                    allids.insert(mirrorid[newr][newc]);
                }

                else
                vis[newr][newc][dir] = true;
                
                q.push({newr, newc});
            }
        }

        if ((ll)allids.size() == mirror)
        {
            cout << 2 << endl;
            cout << "E" << i << " ";

            if (dir == 0)
            {
                if (lastc == 1)
                cout << "W" << lastr << endl;

                else
                cout << "E" << lastr << endl;
            }

            else
            {
                if (lastr == 1)
                cout << "N" << lastc << endl;

                else
                cout << "S" << lastc << endl;
            }

            return;
        }
    }    

    cout << ans.size() << endl;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
   // cin >> cases;

    while (cases--)
    {
        solve();
    }
}