#include <iostream>
#include <queue>
using namespace std;

int main()
{
    //descending
    priority_queue<int> pq;

    //ascending
    priority_queue<int, vector<int>, greater<int>> pq2;

    //pq of pirs
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq3;
    
    pq.push(9);
    pq.push(8);
    pq.push(6);

    // Create a copy
    priority_queue<int> temp(pq);
    while (!temp.empty())
    {
        cout << temp.top() << " ";
        temp.pop();
    }
    return 0;
}