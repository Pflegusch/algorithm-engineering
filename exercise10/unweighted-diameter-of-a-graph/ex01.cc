#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include "bits/stdc++.h"

using namespace std;

void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt)
{
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

vector<int> bfs(vector<pair<int, int>> adj[], int s, int t, int n)
{
    // Initialize queue, vector which holds path for each iteration and
    // vector for all visited nodes
    queue<vector<int>> q;
    vector<bool> visited(n, false);
    vector<int> path;

    // Push back s into the path, as it has to be in the resulting path
    // as well as the path to the current queue q, mark s as visited
    path.push_back(s);
    q.push(path);
    visited[s] = true;

    // While there are still nodes to visit
    while (!q.empty())
    {
        // Get the current path and extract the last node of it
        path = q.front();
        q.pop();
        int last = path[path.size() - 1];
        // If the last node extracted is the destination node, the path is found
        // and one can start to calculate the weight of that path
        if (last == t)
        {
            return path;
        }
        // Mark newly visited nodes as marked and add them to the new path
        for (auto it = adj[last].begin(); it != adj[last].end(); it++)
        {
            if (!visited[it->first])
            {
                visited[it->first] = true;
                vector<int> newpath(path);
                newpath.push_back(it->first);
                q.push(newpath);
            }
        }
    }
    return path;
}

void printGraph(vector<pair<int, int>> adj[], int V)
{
    int v, w;
    for (int u = 1; u <= V; u++)
    {
        cout << "Node " << u << " makes an edge with" << endl;
        for (auto it = adj[u].begin(); it != adj[u].end(); it++)
        {
            v = it->first;
            w = it->second;
            cout << "\tNode " << v << " with edge weight = "
                 << w << endl;
        }
        cout << endl;
    }
}

void solution(vector<pair<int, int>> adj[], int n)
{
    unsigned long diameter = 0;
    vector<vector<int>> paths;

    for (int s = 1; s <= n; s++)
    {
        for (int t = s + 1; t <= n; t++)
        {
            if (s == t)
            {
                continue;
            }
            vector<int> current_path = bfs(adj, s, t, n);
            paths.push_back(current_path);
            diameter = max(diameter, current_path.size() - 1);
        }
    }
    cout << diameter << endl;

    for (const vector<int> &path : paths)
    {
        if (path.size() - 1 == diameter)
        {
            cout << path.front() << " " << path.back() << endl;
            break;
        }
    }
}

int main(int argc, char **argv)
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> adj[m];

    for (int i = 0; i < 2 * m; i++)
    {
        int src, dest, w;
        cin >> src >> dest >> w;
        addEdge(adj, src, dest, w);
    }

    for (int u = 1; u <= n; u++)
    {
        sort(adj[u].begin(), adj[u].end());
        adj[u].erase(unique(adj[u].begin(), adj[u].end()), adj[u].end());
        sort(adj[u].begin(), adj[u].end(), [](pair<int, int> a, pair<int, int> b)
             { return a.second < b.second; });
    }

    solution(adj, n);

    return 0;
}
