#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "bits/stdc++.h"

using namespace std;

void addEdge(pair<int, vector<pair<int, int>>> adj[], int u, int v, int wt) {
    adj[u].second.push_back(make_pair(v, wt));
    adj[v].second.push_back(make_pair(u, wt));
}


// Add weight to a given node
void addWeight(pair<int, vector<pair<int, int>>> adj[], int u, int wt) {
    adj[u].first = wt;
}

// Add the degree ti a given node
void applyDegree(pair<int, vector<pair<int, int>>> adj[], 
    pair<int, pair<int, vector<pair<int, int>>>> adj_deg[], 
    int V) 
{
    for (int i = 1; i <= V; i++) {
        adj_deg[i].first = adj[i].second.size();
        adj_deg[i].second = adj[i];
    }
}

void printGraph(pair<int, pair<int, vector<pair<int, int>>>> adj[], int V) {
    int v, w;
    for (int u = 1; u <= V; u++) {
        cout << "Node " << u << " with weight " << adj[u].second.first << 
        " and degree " << adj[u].first << " makes an edge with \n";
        for (auto it = adj[u].second.second.begin(); it != adj[u].second.second.end(); it++) {
            v = it->first;
            w = it->second;
            cout << "\tNode " << v << " (w = " << adj[v].second.first << ", d = " << adj[v].first << ") with edge weight = "
                 << w << "\n";
        }
        cout << "\n";
    }
}

// Add both the weight and the degree to create a "priority list" that priorites verticies with the 
// highest weight + degree
vector<pair<int, int>> addWeightAndDegree(pair<int, pair<int, vector<pair<int, int>>>> adj[], int V) {
    vector<pair<int, int>> result(V);
    for (int i = 0; i < V; i++) {
        result[i].first = i + 1;
        result[i].second = adj[i + 1].first + adj[i + 1].second.first;
    }
    return result;
}

// Function to check the independent set, if all verticies get reached from a given subgraph, a IS is found
bool checkIfAllNodesReached(pair<int, pair<int, vector<pair<int, int>>>> graph[], int V) {
    // Mark all visited nodes
    vector<bool> visited(V + 1, false);
    visited[0] = true;

    // Mark all nodes as visited that the subgraph can reach
    for (int u = 1; u <= V; u++) {
        auto it = graph[u].second.second.begin();
        if (it != graph[u].second.second.end()) {
            visited[u] = true;
            while (it != graph[u].second.second.end()) {
                visited[it->first] = true; 
                it++;
            }
        }
    }

    // If all verticies got visited, the IS is found
    for (bool vis : visited) {
        if (!vis) return false;
    }
    return true;
}

void solve(pair<int, pair<int, vector<pair<int, int>>>> graph[],
        vector<pair<int, int>> prio, 
        pair<int, pair<int, vector<pair<int, int>>>> adj[], 
        int V, int m) 
{
    int nodes = 0;
    vector<int> node_set;

    // For each vertex from the "priority list", add it to a subgraph and check if its and IS,
    // otherwise take the next vertex in the list and recheck
    for (pair<int, int> node : prio) {
        graph[node.first] = adj[node.first];
        node_set.push_back(node.first);
        nodes++;
        if (checkIfAllNodesReached(graph, V)) break;
    }

    // Amount of nodes
    cout << nodes << endl;

    // Weight of nodes
    int weight = 0;
    for (int &node : node_set) {
        weight += adj[node].second.first;
    }
    cout << weight << endl;

    // Nodes
    for (int &node : node_set) {
        cout << node << " ";
    }
    cout << endl;
}

int main(int argc, char** argv) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, m, w;
    cin >> n >> m;
    pair<int, vector<pair<int, int>>> adj[m];
    pair<int, pair<int, vector<pair<int, int>>>> adj_deg[m], graph[m];
    
    for (int i = 0; i < 2*m; i++) {
        int src, dest, w;
        cin >> src >> dest >> w;
        addEdge(adj, src, dest, w);
    }

    for (int i = 1; i <= n; i++) {
        cin >> w;
        addWeight(adj, i, w);
    }

    // Erase duplicates and sort adj after weights to always have the smallest one at the top
    // Necessary for the above implementation to work
    for (int u = 1; u <= n; u++) {
        sort(adj[u].second.begin(), adj[u].second.end());
        adj[u].second.erase(unique(adj[u].second.begin(), adj[u].second.end()), adj[u].second.end());
    }

    // Apply the current degree to each node
    applyDegree(adj, adj_deg, n);

    // Create a priority list that contains the sum of the weight and degree of each node
    vector<pair<int, int>> prio = addWeightAndDegree(adj_deg, n);
    sort(prio.begin(), prio.end(), [](const pair<int, int> & p1, const pair<int, int> & p2) {
        return p1.second > p2.second;
    });
    solve(graph, prio, adj_deg, n, m);

    return 0;
}
