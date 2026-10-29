#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef long long       ll;
// typedef long double     double;
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
#define double long double

const ll MOD = 1e9 + 7;//998244353;
const ll INF = 9e18;
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 20;

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

double p, q;
ll k1, k2;

double dp[51][51];
bool vis[51][51];

double func(int ck1, int ck2)
{
    if (ck1 == 0 || ck2 == 0) return 0;
    if (vis[ck1][ck2]) return dp[ck1][ck2];

    cout << ck1 << " " << ck2 << endl;

    return dp[ck1][ck2] = p * (1.0 + func(ck1 - 1, k2)) + q * (1.0 + func(k1, ck2 - 1));
}

void solve()
{
    memset(vis, false, sizeof(vis));
    cin >> p >> k2 >> k1;

    q = 1.0 - p;

    cout << fixed << setprecision(6) << func(k1, k2) << endl;
}

void solve2()
{
    cin >> p >> k2 >> k1;
    q = 1.0 - p;

    vector< vector<double> > v(2, vector<double> (3, 0));
    vector<double> ans;

    vector<double> pp (k1 + 10), qq (k2 + 10);

    double curp = 1.0, curq = 1.0;
    
    FOR(i, 1, k1 + 3) 
    {
        curp *= p;
        pp[i] = pp[i - 1] + curp;
    }

    FOR(i, 1, k2 + 3)
    {
        curq *= q;
        qq[i] = qq[i - 1] + curq;
    }

    v[0][0] = 1, v[0][1] = -1 * (pp[k1 - 1]), v[0][2] = pp[k1];
    v[1][0] = -1 * qq[k2 - 1], v[1][1] = 1, v[1][2] = qq[k2];

    int k = Gauss(v, ans);
    cout << fixed << setprecision(2) << abs(ans[0]) + abs(ans[1]) << endl;
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
        solve2();
    }
}