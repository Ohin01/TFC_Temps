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

ll Bigmod(ll a, ll b, ll m){
    if(b == 0) return 1 % m;
    ll x = Bigmod(a, b / 2LL, m);
    x = (x * x) % m;
    if(b % 2 == 1) x = (x * a) % m;
    return x;
}



const ll MOD = 1e9 + 7;//998244353;

const ll INF = 9e18;

const int MAX = 2e5 + 5;

const int MX = 1e6 + 5;

const int LOGN = 20;

const ld PI = acos((ld) -1);



int nxt[MAX];

int state[MAX];

vi color(MAX, -1);

int id = 1;



void dfs(int node)

{

	state[node] = 1;



	int v = nxt[node];



	if (state[v] == 0)

	{

		dfs(v);

	}



	else if (state[v] == 1)

	{

		int start = v;

		int cur = start;



		do {

			color[cur] = id;

			cur = nxt[cur];

		} while (cur != start);



		id++;

	}



	state[node] = 2;

}



void solve()
{
	ll n;
	cin >> n;

	vll a(n + 1), p(n + 1);

	FOR(i, 1, n + 1) cin >> p[i];
	FOR(i, 1, n + 1) cin >> a[i];

	vvi rev(n + 1);

	FOR(i, 1, n + 1)
	{
		nxt[p[i]] = i;
	}

	FOR(i, 1, n + 1)
	{
		if (state[i] == 0) dfs(i);
	}
	//FOR(i, 1, n + 1) cout << nxt[i] << " "; cout << endl;
	//FOR(i, 1, n + 1) cout << color[i] << " "; cout << endl;

	ll req = color[1];
	ll mn = INF;
	ll cur = -1;
	FOR(i, 1, n + 1)
	{
		if (color[i] == req && a[i] < mn)
		{
			mn = a[i];
			cur = i;
		};
	}

	ll times = 0;

	while (cur != 1)
	{
		times++;
		cur = nxt[cur];
	}

	set<int> s;

	FOR(i, 1, n + 1) s.insert(color[i]);

	ll sz = s.size();

	vvi comp(sz + 1);
	vvi val(sz + 1);
	vb hoise(sz + 1);

	FOR(i, 1, n + 1)
	{
		ll c = color[i];
		if (hoise[color[i]]) continue;

		hoise[color[i]] = true;

		ll st = i;
		ll achi = i;

		do {
			val[color[i]].pb(a[achi]);
			comp[color[i]].pb(achi);
			achi = nxt[achi];
		} while(st != achi);

		reverse(val[c].begin(), val[c].end());
		reverse(comp[c].begin(), comp[c].end());
	}

	vb vis(sz + 1);
	vll ans(n + 1);

    ll r = 0;
	ll v = 0; 

    FOR(i, 1, n + 1)
    {
        ll c = color[i];
		ll sz = val[c].size();

        if (vis[color[i]]) continue;
        vis[color[i]] = true;

        ll mn = INF;
		ll l = -1;
        ll gc;

        if (i == 1) gc = 1;
        else gc = __gcd(v, sz); 

		ll st = (r + gc) % sz;
		if (st == 0) st += sz;

        for (int j = st; j <= sz; j += gc)
        {
			if (val[c][j - 1] < mn)
			{
				mn = val[c][j - 1];
				l = j;
			}
        }

		ll achi = i;
		ll ind = l - 1;

		FOR(j, 0, sz)
		{
			ans[achi] = val[c][ind];
			ind--;

            if (ind < 0) ind += val[c].size();
			ind %= val[c].size();
			achi = nxt[achi];
		}

		// cout << "gc: " << gc << endl;
		// cout << l << " " << sz << endl;

		if (i == 1)
		{
			r = l;
			v = sz;
		}

		else
		{
			ll ba = (l - r + sz) % sz;
			ll left = v / gc;
			ll right = (l - r) / gc;
			ll md = sz / gc;

			if (md == 1)
			{

			}
			ll k = (Bigmod(left, md - 2, md) * right) % md;
			r = r + v * k;
			v = lcm(v, sz);

			r %= v;
			r += v;
			r %= v;

			v %= sz;
		}

		//cout << r << " "  << v << endl;
		
		//cout << mn << " " << gc << " " << lst << " " << l << endl;

		//FOR(i, 1, n + 1) cout << ans[i] << " "; cout << endl;
    }


	FOR(i, 1, n + 1) cout << ans[i] << " ";
	cout << endl;

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