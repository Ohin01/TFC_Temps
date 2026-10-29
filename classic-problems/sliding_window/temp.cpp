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

void solve()
{
    ordered_multiset<int> s;
    s.insert(2);
    s.insert(3);
    s.insert(4);

    cout << (s.order_of_key(3)) << endl;

    for (int i = 0; i < s.size(); i++)
    {
        cout << (*s.find_by_order(i)) << " ";
    } cout << endl;

    s.insert(2);
    s.insert(3);
    s.insert(4);

    auto it = s.find_by_order(s.order_of_key(3));

    s.erase(it);

    cout << (s.order_of_key(3)) << endl;

    for (int i = 0; i < s.size(); i++)
    {
        cout << (*s.find_by_order(i)) << " ";
    } cout << endl;
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