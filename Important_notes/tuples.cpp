#include <bits/stdc++.h>
using namespace std;

struct Compare {
    bool operator()(const tuple<int,int,int>& a, const tuple<int,int,int>& b) const {
        // Example:
        // 1) sort by 2nd element ASC
        // 2) if tie, by 3rd DESC
        // 3) if tie, by 1st ASC

        if (get<1>(a) != get<1>(b))
            return get<1>(a) < get<1>(b);

        if (get<2>(a) != get<2>(b))
            return get<2>(a) > get<2>(b);

        return get<0>(a) < get<0>(b);
    }
};

int main() 
{
    // 1. Creating tuples
    tuple<int,int,int> t1(1, 2, 3);
    auto t2 = make_tuple(4, 5, 6);

    // 2. Access / modify
    cout << get<0>(t1) << "\n"; // 1
    get<1>(t1) = 10;

    // 3. Unpacking
    int a, b, c;
    tie(a, b, c) = t1;

    // ignore example
    tie(a, ignore, c) = t2;

    // 4. Vector of tuples
    vector<tuple<int,int,int>> v;

    v.emplace_back(3, 2, 1);
    v.emplace_back(1, 5, 4);
    v.emplace_back(2, 2, 5);
    v.emplace_back(1, 2, 3);

    // 5. Default sorting (lexicographic)
    sort(v.begin(), v.end());

    for (auto &t: v)
    {
        cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl; 
    }

    sort(v.begin(), v.end(), [](auto &a, auto &b) {
        // sort by 3rd element DESC
        return get<2>(a) > get<2>(b);
    });

    // 7. Custom sorting (struct comparator)
    sort(v.begin(), v.end(), Compare());

    // 8. Tuple comparison
    tuple<int,int> p1 = {1,2};
    tuple<int,int> p2 = {1,3};

    if (p1 < p2) {
        cout << "\np1 < p2 (lexicographic works)\n";
    }

    // 9. Tuple in priority_queue

    // Min-heap based on tuple (lexicographic)
    priority_queue<
        tuple<int,int,int>,
        vector<tuple<int,int,int>>,
        greater<tuple<int,int,int>>
    > pq;

    pq.push({3,2,1});
    pq.push({1,5,4});
    pq.push({2,2,5});

    return 0;
}