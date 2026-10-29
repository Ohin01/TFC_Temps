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
const int MX = 1e5 + 5;
const int LOGN = 20;
const ld PI = acos((ld) -1);

// vector<ll> spf(MX);
// vll primes;

// void sieve()
// {
//     for (int i = 0; i < MX; i++) spf[i] = i;

//     for (int i = 2; i * i < MX; i++) {
//         if (spf[i] == i) {
//             for (int j = i * i; j < MX; j += i) {
//                 if (spf[j]== j)
//                     spf[j] = i;
//             }
//         }
//     }
// }

// vector<ll> getPrimeFactors(int x)
// {
//     vector<ll> ret;
//     while (x != 1) {
//         ret.push_back(spf[x]);
//         x = x / spf[x];
//     }
//     return ret;
// }

// void fill()
// {
//     FOR(i, 2, MX) if (spf[i] == i) primes.pb(i - 1);
// }

//vi dp(MX, 2);

vector<int> sieve(const int N, const int Q = 17, const int L = 1 << 15) {
  static const int rs[] = {1, 7, 11, 13, 17, 19, 23, 29};
  struct P { 
    P(int p) : p(p) {}
    int p; int pos[8];
  };
  auto approx_prime_count = [] (const int N) -> int {
    return N > 60184 ? N / (log(N) - 1.1)
                     : max(1., N / (log(N) - 1.11)) + 1;
  };

  const int v = sqrt(N), vv = sqrt(v);
  vector<bool> isp(v + 1, true);
  for (int i = 2; i <= vv; ++i) if (isp[i]) {
    for (int j = i * i; j <= v; j += i) isp[j] = false;
  }

  const int rsize = approx_prime_count(N + 30);
  vector<int> primes = {2, 3, 5}; int psize = 3;
  primes.resize(rsize);

  vector<P> sprimes; size_t pbeg = 0;
  int prod = 1; 
  for (int p = 7; p <= v; ++p) {
    if (!isp[p]) continue;
    if (p <= Q) prod *= p, ++pbeg, primes[psize++] = p;
    auto pp = P(p); 
    for (int t = 0; t < 8; ++t) {
      int j = (p <= Q) ? p : p * p;
      while (j % 30 != rs[t]) j += p << 1;
      pp.pos[t] = j / 30;
    }
    sprimes.push_back(pp);
  }

  vector<unsigned char> pre(prod, 0xFF);
  for (size_t pi = 0; pi < pbeg; ++pi) {
    auto pp = sprimes[pi]; const int p = pp.p;
    for (int t = 0; t < 8; ++t) {
      const unsigned char m = ~(1 << t);
      for (int i = pp.pos[t]; i < prod; i += p) pre[i] &= m;
    }
  }

  const int block_size = (L + prod - 1) / prod * prod;
  vector<unsigned char> block(block_size); unsigned char* pblock = block.data();
  const int M = (N + 29) / 30;

  for (int beg = 0; beg < M; beg += block_size, pblock -= block_size) {
    int end = min(M, beg + block_size);
    for (int i = beg; i < end; i += prod) {
      copy(pre.begin(), pre.end(), pblock + i);
    }
    if (beg == 0) pblock[0] &= 0xFE;
    for (size_t pi = pbeg; pi < sprimes.size(); ++pi) {
      auto& pp = sprimes[pi];
      const int p = pp.p;
      for (int t = 0; t < 8; ++t) {
        int i = pp.pos[t]; const unsigned char m = ~(1 << t);
        for (; i < end; i += p) pblock[i] &= m;
        pp.pos[t] = i;
      }
    }
    for (int i = beg; i < end; ++i) {
      for (int m = pblock[i]; m > 0; m &= m - 1) {
        primes[psize++] = i * 30 + rs[__builtin_ctz(m)];
      }
    }
  }
  assert(psize <= rsize);
  while (psize > 0 && primes[psize - 1] > N) --psize;
  primes.resize(psize);
  return primes;
}

const int MAXN = 1e9 + 1;
bitset<MAXN> all;
bitset<MAXN> isPrime;

void solve()
{
    int n;
    cin >> n;
    
    if (all[n] == 1) cout << "Alice" << endl;
    else cout << "Bob" << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    auto primes = sieve(MAXN);
    
    //cout << primes.size() << endl;

    for (auto p: primes)
    {
        //if (p != 2) 
        isPrime.set(p - 1);
    }
    
    //all |= (isPrime);
    
    ll cnt = 0;
    
    FOR(i, 0, MAXN)
    {
        if (all[i] == 0)
        {
            cnt++;
            //cout << i << endl;
            all |= (isPrime << (i));
        }
    }
    //cout << cnt << endl;


    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}