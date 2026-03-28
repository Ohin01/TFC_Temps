#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9; // Maximum array size

struct PST {
    struct node {
        int l = 0, r = 0; // Children indices
        long long val = 0; // Value stored in the node (sum)
    } t[20 * N]; // Enough nodes for persistent tree
    int T = 0; // Total number of nodes created

    // Build an empty segment tree for range [b, e]
    int build(int b, int e) {
        int cur = ++T; // create a new node
        if (b == e) return cur; // leaf node
        int mid = (b + e) / 2;
        t[cur].l = build(b, mid);
        t[cur].r = build(mid + 1, e);
        t[cur].val = t[t[cur].l].val + t[t[cur].r].val;
        return cur;
    }

    // Update the value at position i by v, based on previous version `pre`
    int upd(int pre, int b, int e, int i, int v) {
        int cur = ++T; // create new node
        t[cur] = t[pre]; // copy previous node
        if (b == e) { // leaf node
            t[cur].val += v;
            return cur;
        }
        int mid = (b + e) / 2;
        if (i <= mid) t[cur].l = upd(t[pre].l, b, mid, i, v); // update left
        else t[cur].r = upd(t[pre].r, mid + 1, e, i, v); // update right
        t[cur].val = t[t[cur].l].val + t[t[cur].r].val; // update current sum
        return cur;
    }

    // Query sum in range [l, r] for current tree rooted at `cur`
    long long query(int cur, int b, int e, int l, int r) {
        if (r < b || e < l) return 0; // no overlap
        if (l <= b && e <= r) return t[cur].val; // complete overlap
        int mid = (b + e) / 2;
        return query(t[cur].l, b, mid, l, r) + query(t[cur].r, mid + 1, e, l, r);
    }
} t;

int root[N]; // stores root of each version
int a[N];

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) cin >> a[i];

    // Build the initial empty tree
    root[0] = t.build(1, n);

    // Build versions for each prefix of array
    for (int i = 1; i <= n; i++) {
        root[i] = t.upd(root[i - 1], 1, n, i, a[i]);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << t.query(root[r], 1, n, l, r) << "\n";
    }

    return 0;
}
