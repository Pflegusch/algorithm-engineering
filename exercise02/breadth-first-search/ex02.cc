#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include "bits/stdc++.h"

using namespace std;

inline void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt) {
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

vector<int> bfs(vector<pair<int, int>> adj[], int s, int t, int n, int* weight) {
    if (s == t) {
        return vector<int>(1, s);
    }

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
    while (!q.empty()) {
        // Get the current path and extract the last node of it
        path = q.front();
        q.pop();
        int last = path[path.size() - 1];
        // If the last node extracted is the destination node, the path is found
        // and one can start to calculate the weight of that path
        if (last == t) {
            // For all nodes in the path, add the weight of each edge
            // If the edge is found and added to the weight variable, one can
            // simpy go to the next node in the adj matrix
            for (int i = 0; i < path.size() - 1; i++) {
                auto it = adj[path[i]].begin();
                while (it < adj[path[i]].end()) {
                    if (it->first == path[i + 1]) {
                        *weight += it->second;
                        it = adj[it->first].begin();
                        break;
                    }
                    it++;
                }
            }
            return path;
        }
        // Mark newly visited nodes as marked and add them to the new path
        for (auto it = adj[last].begin(); it != adj[last].end(); it++) {
            if (!visited[it->first]) {
                visited[it->first] = true;
                vector<int> newpath(path);
                newpath.push_back(it->first);
                q.push(newpath);
            }
        }
    }
    return path;
}

int main(int argc, char** argv) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, m, s, t;
    cin >> n >> m;
    vector<pair<int, int>> adj[m];
    
    for (int i = 0; i < 2*m; i++) {
        int src, dest, w;
        cin >> src >> dest >> w;
        addEdge(adj, src, dest, w);
    }

    cin >> s >> t;

    int weight = 0;
    vector<int> path = bfs(adj, s, t, n, &weight);
    cout << path.size() - 1 << endl;
    cout << weight << endl;
    for (auto &elem : path) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}
