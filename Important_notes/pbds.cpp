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

void pbds_set()
{
    ordered_set<int> s;

    s.insert(10);
    s.insert(20);
    s.insert(30);

    // 1. find_by_order(k)
    // returns iterator to k-th element (0-based)
    cout << *s.find_by_order(0) << "\n"; // 10
    cout << *s.find_by_order(2) << "\n"; // 30

    // 2. order_of_key(x)
    // returns number of elements STRICTLY LESS than x
    cout << s.order_of_key(20) << "\n"; // 1
    cout << s.order_of_key(25) << "\n"; // 2

    // 3. erase
    s.erase(20);

    for (auto x : s) cout << x << " ";
}

void pbds_map()
{
    ordered_map<int, string> mp;

    mp[10] = "A";
    mp[20] = "B";
    mp[30] = "C";

    // 1. find_by_order(k)
    auto it = mp.find_by_order(1);
    cout << it->first << " " << it->second << "\n"; // 20 B

    // 2. order_of_key(x)
    cout << mp.order_of_key(25) << "\n"; // 2/
}

int main(void)
{
    pbds_set();
}