#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

vector<int> adj[MAXN];
int sz[MAXN], heavy[MAXN];
int tin[MAXN], tout[MAXN], node[MAXN];
int tt = 0;

void dfs(int u, int p) 
{
    sz[u] = 1;
    heavy[u] = -1;
    node[tt] = u;
    tin[u] = tt++; 
    
    int max_sz = 0;

    for (int v : adj[u]) 
    {
        if (v != p) 
        {
            dfs(v, u);
            sz[u] += sz[v];

            if (sz[v] > max_sz) 
            {
                max_sz = sz[v];
                heavy[u] = v;
            }
        }
    }
    
    tout[u] = tt - 1;
}

void dsu(int u, int p, bool keep) 
{
    for (int v : adj[u]) 
    {
        if (v != p && v != heavy[u]) 
        {
            dsu(v, u, 0); 
        }
    }

    if (heavy[u] != -1) 
    {
        dsu(heavy[u], u, 1);
    }

    for (int v : adj[u]) 
    {
        if (v != p && v != heavy[u]) 
        {
            for (int t = tin[v]; t <= tout[v]; t++) 
            {
                int w = node[t]; //subtree of child in subtree of parent
            }
        }
    }

    //Add node u itself
    

    //Answer Queries for u here
    // ...

    //Clear if needed
    if (keep == 0) 
    {
        for (int t = tin[u]; t <= tout[u]; t++) 
        {
            int w = node[t];
        }
    }
}

void solve()
{
    
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    while (cases--)
    {
        solve();
    }
}