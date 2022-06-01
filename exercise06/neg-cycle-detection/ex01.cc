#include <vector>
#include <iostream>
#include <algorithm>
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

void solve(pair<int, vector<pair<int, int>>> adj[], int V, int E)
{
    vector<int> vis(V, 0);
    int dist[V], parent[V];

    // Step 1: Initialize distances from 1
    // to all other vertices as INFINITE
    for (int i = 0; i <= V; i++)
    {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[1] = 0;
    vis[1] = 0;

    bool flag = true;
    for (int i = 1; i <= V - 1; i++)
    {
        if (!flag)
            break;
        flag = false;
        for (auto it = adj[i].second.begin(); it != adj[i].second.end(); it++)
        {
            int u = i;
            int v = it->first;
            int w = it->second;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            {
                flag = true;
                vis[v] = 1;
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    int c = -1;
    for (int i = 1; i <= V; i++)
    {
        for (auto it = adj[i].second.begin(); it != adj[i].second.end(); it++)
        {
            int u = i;
            int v = it->first;
            int w = it->second;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            {
                c = v;
                break;
            }
        }
    }

    if (c != -1)
    {
        for (int i = 1; i <= V; i++)
        {
            cout << c << " ";
            c = parent[c];
        }

        // vector<int> cycle;
        // for (int v = c;; v = parent[v])
        // {
        //     cycle.push_back(v);
        // if (v == c && cycle.size() > 1)
        //     break;
        // }
        // reverse(cycle.begin(), cycle.end());
        // for (int v : cycle)
        // {
        //     cout << v << " ";
        // }
        // cout << endl;
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
    solve(adj, n, m);

    return 0;
}