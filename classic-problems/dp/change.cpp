vll nextGreaterRight(vll &a) 
{
    ll n = a.size();
    vll right(n, -1);
    stack<ll> st; // indices

    for (ll i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            right[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return right;
}

vll nextGreaterLeft(vll &a) 
{
    ll n = a.size();
    vll left(n, -1);
    stack<ll> st;

    for (ll i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] <= a[i]) {
            st.pop();
        }
        if (!st.empty()) left[i] = st.top();
        st.push(i);
    }
    return left;
}