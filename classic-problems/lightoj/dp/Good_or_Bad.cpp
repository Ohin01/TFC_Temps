#include<bits/stdc++.h>
using namespace std;

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

string s;
ll n;

bool isVowel(char c)
{
    if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') return true;
    else return false;
}

bool isConst(char c)
{
    if (!isVowel(c) && c >= 'A' && c <= 'Z') return true;
    else return false;
}

bool leftC(int ind)
{
    int cnt = 1;

    for (int i = ind - 1; i >= ind - 4; i--)
    {
        if (i < 1) break;

        if (s[i] == '?') cnt++;
        else if (isVowel(s[i])) break;
        else cnt++;
    }

    if (cnt == 5) return true;
    else return false;
}


bool leftV(int ind)
{
    int cnt = 1;

    for (int i = ind - 1; i >= ind - 2; i--)
    {
        if (i < 1) break;

        if (s[i] == '?') cnt++;
        else if (isVowel(s[i])) cnt++;
        else break;
    }

    if (cnt == 3) return true;
    else return false;
}

bool rightC(int ind)
{
    int cnt = 1;

    for (int i = ind + 1; i <= ind + 4; i++)
    {
        if (i > n) break;

        if (s[i] == '?') cnt++;
        else if (isVowel(s[i])) break;
        else cnt++;
    }

    if (cnt == 5) return true;
    else return false;
}

bool rightV(int ind)
{
    int cnt = 1;

    for (int i = ind + 1; i <= ind + 2; i++)
    {
        if (i > n) break;

        if (s[i] == '?') cnt++;
        else if (isVowel(s[i])) cnt++;
        else break;
    }

    if (cnt == 3) return true;
    else return false;
}

void solve()
{
    
    cin >> s;
    n = s.size();
    s = "#" + s;
    FOR(i, 0, 10) s += "#";

    ll c = 0, v = 0;
    bool bad = false;

    FOR(i, 1, n + 1)
    {
        if (c >= 5 || v >= 3) 
        {
            cout << "BAD" << endl;
            return;
        }

        if (s[i] == '?')
        {   
            c = 0;
            v = 0;
        }

        else if (isVowel(s[i])) 
        {
            v++;
            c = 0;
        }

        else
        {
            c++;
            v = 0;
        }
    }

    if (c >= 5 || v >= 3)
    {
        cout << "BAD" << endl;
        return;
    }

    bool mixed = false;

    FOR(i, 1, n + 1)
    {
        if (isConst(s[i]))
        {
            if (leftC(i) || rightC(i)) mixed = true;
        }

        else if (isVowel(s[i]))
        {
            if (leftV(i) || rightV(i)) mixed = true;
        }

        else
        {
            if (leftC(i) || leftV(i) || rightC(i) || rightV(i)) mixed = true;
        }
    }

    vector<vector<bool>> dp(n + 10, vb(2, false));

    FORR(i, n, 1)
    {
        if (s[i] == '?')
        {
            ll cnt = 1;

            FOR(j, i + 1, i + 3)
            {
                if (isVowel(s[j])) cnt++;
                else break;
            }

            if (cnt == 3) dp[i][1] = true;
            if (cnt == 2 && s[i + 2] == '?' && dp[i + 2][0] == true) dp[i][1] = true;

            cnt = 1;

            FOR(j, i + 1, i + 5)
            {
                if (isConst(s[j])) cnt++;
                else break;
            }

            if (cnt == 5) dp[i][0] = true;
            if (cnt == 4 && s[i + 4] == '?' && dp[i + 4][1] == true) dp[i][0] = true;
        }

        else if (isVowel(s[i]))
        {
            ll cnt = 1;

            FOR(j, i + 1, i + 3)
            {
                if (isVowel(s[j])) cnt++;
                else break;
            }

            if (cnt == 2 && s[i + 2] == '?' && dp[i + 2][0] == true)
            {
                cout << "BAD" << endl;
                return;
            }
        }

        else
        {
            ll cnt = 1;

            FOR(j, i + 1, i + 5)
            {
                if (isConst(s[j])) cnt++;
                else break;
            }

            if (cnt == 4 && s[i + 4] == '?' && dp[i + 4][1] == true)
            {
                cout << "BAD" << endl;
                return;
            }
        }
    }

    //if (bad == true) cout << "BAD" << endl;
    if (mixed == true) cout << "MIXED" << endl;
    else cout << "GOOD" << endl;
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