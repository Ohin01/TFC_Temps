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

const double eps = 1e-9;
int Gauss(vector<vector<double>> a, vector<double> &ans) {
  int n = (int)a.size(), m = (int)a[0].size() - 1;
  vector<int> pos(m, -1);
  double det = 1; int rank = 0;
  for(int col = 0, row = 0; col < m && row < n; ++col) {
    int mx = row;
    for(int i = row; i < n; i++) if(fabs(a[i][col]) > fabs(a[mx][col])) mx = i;
    if(fabs(a[mx][col]) < eps) {det = 0; continue;}
    for(int i = col; i <= m; i++) swap(a[row][i], a[mx][i]);
    if (row != mx) det = -det;
    det *= a[row][col];
    pos[col] = row;
    for(int i = 0; i < n; i++) {
      if(i != row && fabs(a[i][col]) > eps) {
        double c = a[i][col] / a[row][col];
        for(int j = col; j <= m; j++) a[i][j] -= a[row][j] * c;
      }
    }
    ++row; ++rank;
  }
  ans.assign(m, 0);
  for(int i = 0; i < m; i++) {
    if(pos[i] != -1) ans[i] = a[pos[i]][m] / a[pos[i]][i];
  }
  for(int i = 0; i < n; i++) {
    double sum = 0;
    for(int j = 0; j < m; j++) sum += ans[j] * a[i][j];
    if(fabs(sum - a[i][m]) > eps) return -1; //no solution
  }
  for(int i = 0; i < m; i++) if(pos[i] == -1) return 2; //infinte solutions
  return 1; //unique solution
}

ll sp[110];
double dp[110];

double func(ll cell)
{
    //if (cell < 0) return 0;
    if (cell >= 100) return 0;
    if (dp[cell] >= 0) return dp[cell];

    if (sp[cell] == -1)
    {
        double tot = 0;
        ll cnt = 0;

        FOR(i, 1, 7)
        {
            //cout << i << " " << tot << endl;
            if (cell + i > 100)
            {
                tot += (1.0 / 6.0);
                continue;;
            }
            tot += (1 + func(cell + i)) * (1.0 / 6.0);
            cnt++;
        }
        //cout << cnt << " " << tot << " " << tot / (cnt * 1.0) * 6.0 << endl;

        return dp[cell] = tot / (1.0 * cnt) * 6.0;
    }

    else
    {
        return dp[cell] = func(sp[cell]);
    }
}

void solve()
{
    ll n;
    cin >> n;

    FOR(i, 0, 105)
    {
        sp[i] = -1;
        dp[i] = -1;
    } 

    FOR(i, 0, n)
    {
        ll a, b;
        cin >> a >> b;

        sp[a] = b;
    }

    dp[100] = dp[101] = dp[102] = dp[103] = dp[104] = dp[105] = dp[106] = 0; 

    vector< vector<double> > v(100, vector<double> (101, 0));
    vector<double> ans;

    FOR(i, 1, 101)
    {
        if (i == 100)
        {
            v[99][99] = 1;
        }
        else if (sp[i] == -1)
        {
            v[i - 1][i - 1] = 6;
            v[i - 1][100] = -6;

            FOR(j, i + 1, i + 7)
            {
                if (j > 100) v[i - 1][i - 1] -= 1;
                else v[i - 1][j - 1] = -1;
            }
        }

        else
        {
            v[i - 1][i - 1] = 1;
            v[i - 1][sp[i] - 1] = -1;
        }
    }

    int k = Gauss(v, ans);
    cout << fixed << setprecision(6) << abs(ans[0]) << endl;

    //cout << fixed << setprecision(6) << func(1) << endl;
}

// int main() {
//   int n, m; cin >> n >> m;
//   vector< vector<double> > v(n);
//   for(int i = 0; i < n; i++) {
//     for(int j = 0; j <= m; j++) {
//       double x; cin >> x; v[i].push_back(x);
//     }
//   }
//   vector<double> ans;
//   int k = Gauss(v, ans);
//   if(k) for(int i = 0; i < n; i++) cout << fixed << setprecision(5) << ans[i] << ' ';
//   else cout << "no solution\n";
//   return 0;
// }

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