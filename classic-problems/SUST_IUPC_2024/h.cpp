#include <bits/stdc++.h>
using namespace std;

const int nax = 1e5 + 10;
const long long inf = 1e18;

pair<long long, long long>seg[nax * 4]; //max min

int n;
int a[nax];
long long pre[nax];


pair<long long, long long>mergeNode(pair<long long, long long>p, pair<long long, long long>q) {
    pair<long long, long long>ret;

    ret.first = max(p.first, q.first);
    ret.second = min(p.second, q.second);

    return ret;
}
void build(int l, int r, int v) {
    if(l == r) {
        seg[v] = {pre[l], pre[l]};
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, v*2), build(mid+1, r, v*2+1);

    seg[v] = mergeNode(seg[v*2], seg[v*2+1]);
}

pair<long long, long long> query(int l, int r, int L, int R, int v) {
    if(l >= L && r <= R) return seg[v];
    if(l > R || r < L) return make_pair(-inf, inf);

    int mid = (l + r) / 2;

    return mergeNode(query(l, mid, L, R, v*2), query(mid+1, r, L, R, v*2+1));
}

int nb[nax], pb[nax];
long long solve() {
    pre[0] = 0;
    for(int i=1; i<=n; ++i) {
        pre[i] = pre[i-1] + a[i];
    }
    build(0, n, 1);

    stack<int>st;
    for(int i=1; i<=n; ++i) {
        while(!st.empty() && a[st.top()] < a[i]) {
            nb[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    while(!st.empty()) {
        nb[st.top()] = n+1;
        st.pop();
    }

    for(int i=n; i>0; --i) {
        while(!st.empty() && a[st.top()] < a[i]) {
            pb[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    while(!st.empty()) pb[st.top()] = 0, st.pop();


    long long ret = -inf;

    for(int i=1; i<=n; ++i) {
        auto nq = query(0,n,i,nb[i]-1,1);
        auto pq = query(0,n,pb[i],i-1,1);

        long long nmx = nq.first, nmn = nq.second;
        long long pmx = pq.first, pmn = pq.second;

        long long mxSum = nmx - pmn;

        long long mnSum = nmn - pmx;

        long long curVal = max(a[i] * mxSum, a[i] * mnSum);

        ret = max(ret, curVal);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while(t--) {
        cin>>n;
        for(int i=1; i<=n; ++i) cin>>a[i];

        long long ans = solve();

        cout<<ans<<"\n";
    }
    return 0;
}