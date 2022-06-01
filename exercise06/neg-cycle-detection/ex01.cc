#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "bits/stdc++.h"

using namespace std;

void addEdge(pair<int, vector<pair<int, int>>> adj[], int u, int v, int wt)
{
    adj[u].second.push_back(make_pair(v, wt));
    adj[v].second.push_back(make_pair(u, wt));
}

void addWeight(pair<int, vector<pair<int, int>>> adj[], int u, int wt)
{
    adj[u].first = wt;
}

void printGraph(pair<int, vector<pair<int, int>>> adj[], int V)
{
    int v, w;
    for (int u = 1; u <= V; u++)
    {
        cout << "Node " << u << " makes an edge with \n";
        for (auto it = adj[u].second.begin(); it != adj[u].second.end(); it++)
        {
            v = it->first;
            w = it->second;
            cout << "\tNode " << v << " with edge weight = " << w << "\n";
        }
        cout << "\n";
    }
}

int main(int argc, char **argv)
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n, m, w;
    cin >> n >> m;
    pair<int, vector<pair<int, int>>> adj[m];

    for (int i = 0; i < m; i++)
    {
        int src, dest, w;
        cin >> src >> dest >> w;
        addEdge(adj, src, dest, w);
    }

    for (int i = 1; i <= n; i++)
    {
        cin >> w;
        addWeight(adj, i, w);
    }

    // Erase duplicates and sort adj after weights to always have the smallest one at the top
    // Necessary for the above implementation to work
    for (int u = 1; u <= n; u++)
    {
        sort(adj[u].second.begin(), adj[u].second.end());
        adj[u].second.erase(unique(adj[u].second.begin(), adj[u].second.end()), adj[u].second.end());
    }

    printGraph(adj, n);

    return 0;
}