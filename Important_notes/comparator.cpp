#include<bits/stdc++.h>
using namespace std;

bool cmp(pair<int,int> a, pair<int,int> b) {
    if (a.first == b.first)
        return a.second > b.second;
    return a.first < b.first; //first compare first one
}


bool cmp2(pair<int,int> a, pair<int,int> b) {
    if (a.second == b.second)
        return a.first > b.first;
    return a.second > b.second; //first compare second one
}

int main(void)
{
    vector<pair<int, int>> v;

    v.push_back({1, 2});
    v.push_back({4, 1});
    v.push_back({5, 1});

    sort(v.begin(), v.end(), cmp);

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].first << " " << v[i].second << endl;
    }
}