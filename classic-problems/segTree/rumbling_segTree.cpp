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

ll Bigmod(ll a, ll b, ll m) {
	if(b == 0) return 1 % m;
	ll x = Bigmod(a, b / 2LL, m);
	x = (x * x) % m;
	if(b % 2 == 1) x = (x * a) % m;
	return x;
}

ll fact[MX];
ll inv[MX];
vpll mv = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

void pre() {
	fact[0]=1;
	inv[0]=1;
	FOR(i, 1, MX) {
		fact[i] = (i * fact[i - 1])% MOD;
		inv[i] = Bigmod(fact[i], MOD - 2LL, MOD);
	}
}

ll nCr(ll n, ll r, ll p) {
	if(r > n || r < 0) return 0;
	if(n == r || r == 0) return 1;
	return (((fact[n] * inv[r]) % p ) * inv[n - r]) % p;
}

template <class S, S (* op ) (S, S ), S (* e ) () > struct
	segtree {
public :
	int ceil_pow2 ( int n ) {
		int x = 0;
		while ((1 U << x ) < ( unsigned int ) ( n ) ) x++;
		return x ;
	}
	segtree () : segtree (0) {}
	segtree (int n ) : segtree (std :: vector <S >( n, e () ) )
	{}
	segtree ( const std :: vector <S >& v ) :
		_n ( int ( v . size () ) ) {
		log = ceil_pow2 ( _n ) ;
		size = 1 << log ;
		d = std :: vector <S >(2 * size, e () ) ;
		for ( int i = 0; i < _n ; i ++) d [ size + i ] =
			    v [ i ];
		for ( int i = size - 1; i >= 1; i - -) {
			update ( i ) ;
		}
	}
	void set (int p, S x ) {  // set pth value to x
		assert (0 <= p && p < _n ) ;
		p += size ;
		d [ p ] = x ;
		for ( int i = 1; i <= log ; i ++) update ( p >> i ) ;
	}
	S get ( int p ) { // get pth value of array
		assert (0 <= p && p < _n ) ;
		return d [ p + size ];
	}
	S prod ( int l, int r ) {  // find the result for [l,r)
		assert (0 <= l && l <= r && r <= _n ) ;
		S sml = e (), smr = e () ;
		l += size ;
		r += size ;
		while ( l < r ) {
		if ( l & 1) sml = op ( sml, d [ l ++]) ;
			if ( r & 1) smr = op ( d [ - - r ], smr ) ;
			l > >= 1;
			r > >= 1;
		}

		return op ( sml, smr ) ;
	}
	S all_prod () {
		return d [1];
	}
	template <bool (* f ) ( S ) > int max_right ( int l ) {
// max_right (l, f): Finds the maximum right boundary
		where a predicate f holds .
		return max_right (l, []( S x ) {
			return f ( x ) ;
		}) ;
	}
	template <class F > int max_right (int l, F f ) {
		assert (0 <= l && l <= _n ) ;
		assert ( f ( e () ) ) ;
		if ( l == _n ) return _n ;
		l += size ;
		S sm = e () ;
		do {
			while ( l % 2 == 0) l >>= 1;
			if (! f ( op ( sm, d [ l ]) ) ) {
				while ( l < size ) {
					l = (2 * l ) ;
					if ( f ( op ( sm, d [ l ]) ) ) {
						sm = op ( sm, d [ l ]) ;
						l ++;
					}
				}
				return l - size ;
			}
			sm = op ( sm, d [ l ]) ;
			l ++;
		} while (( l & -l ) != l ) ;
		return _n ;
	}
	template <bool (* f ) ( S ) > int min_left ( int r ) {
		return min_left (r, []( S x ) {
			return f ( x ) ;
		}) ;
	}
	template <class F > int min_left ( int r, F f ) {
		assert (0 <= r && r <= _n ) ;
		assert ( f ( e () ) ) ;
		if ( r == 0) return 0;
		r += size ;
		S sm = e () ;
		do {
			r--;
			while ( r > 1 && ( r % 2) ) r >>= 1;
			if (! f ( op ( d [ r ], sm ) ) ) {
				while ( r < size ) {
					r = (2 * r + 1) ;
					if ( f ( op ( d [ r ], sm ) ) ) {
						sm = op ( d [ r ], sm ) ;
						r--;
					}
				}
				return r + 1 - size ;
			}
			sm = op ( d [ r ], sm ) ;
		} while (( r & -r ) != r ) ;
		return 0;
	}
private :
	int _n, size, log ;
	vector <S> d;
	void update ( int k ) {
		d [ k ] = op ( d [2 * k ], d [2 * k
		                              + 1]) ;
	}
};
using S = pair <int, int >;  // data type
S op ( S a, S b ) {  // operation type
	return min (a, b ) ;
}
S e () { // primary value
	return make_pair ( MOD, MOD ) ;
}

void solve()
{



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