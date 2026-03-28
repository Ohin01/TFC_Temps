#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;

#define FOR(i, a, b) for(ll i = (a); i < (b); i++)
#define FORR(i, a, b) for(ll i = (a); i >= (b); i--)

const ll MOD = 1e9 + 7;
const ll INF = 9e18;
const int MX = 1e6 + 5;

// ----------- Persistent Segment Tree (memory-optimized) -----------

struct Node {
    int val;
    int l, r;
};

const int MAXNODES = 20 * MX;  // safe for n ≤ 1e5 ~ 2e5
Node seg[MAXNODES];
int nodeCnt = 0;

int newNode(int from = 0) {
    ++nodeCnt;
    if (from) seg[nodeCnt] = seg[from];
    else seg[nodeCnt] = {0, 0, 0};
    return nodeCnt;
}

int build(int l, int r) {
    int cur = newNode();
    if (l == r) return cur;
    int mid = (l + r) / 2;
    seg[cur].l = build(l, mid);
    seg[cur].r = build(mid + 1, r);
    return cur;
}

int update(int prev, int pos, int l, int r) {
    int cur = newNode(prev);
    if (l == r) {
        seg[cur].val = seg[prev].val + 1;
        return cur;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) seg[cur].l = update(seg[prev].l, pos, l, mid);
    else seg[cur].r = update(seg[prev].r, pos, mid + 1, r);
    seg[cur].val = seg[seg[cur].l].val + seg[seg[cur].r].val;
    return cur;
}

int query(int node, int ql, int qr, int l, int r) {
    if (!node || ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return seg[node].val;
    int mid = (l + r) / 2;
    return query(seg[node].l, ql, qr, l, mid) + query(seg[node].r, ql, qr, mid + 1, r);
}

// ----------- Main Program -----------

int n;
ll a[MX];
int roots[MX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // coordinate compression (your code)
    ll temp[n + 1];
    temp[0] = 0;
    FOR(i, 1, n + 1)
        temp[i] = a[i];
    sort(temp, temp + n + 1);

    unordered_map<ll, ll> ids;
    ll id = 1;
    FOR(i, 1, n + 1) {
        if (ids.find(temp[i]) == ids.end()) {
            ids[temp[i]] = id;
            id++;
        }
    }

    roots[0] = build(1, n);

    FOR(i, 1, n + 1) {
        roots[i] = update(roots[i - 1], ids[a[i]], 1, n);
    }

    ll ans = 0;
    FOR(i, 1, n + 1) {
        ll curId = ids[a[i]];
        ans += (i - query(roots[i], 1, curId, 1, n)) *
               (query(roots[n], 1, curId - 1, 1, n) - query(roots[i], 1, curId - 1, 1, n));
    }

    cout << ans << '\n';
    return 0;
}
