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

vector<int> bfs(vector<pair<int, int>> adj[], int s, int t, int V, int* weight) {
    if (s == t) {
        return vector<int>(1, s);
    }

    // Initialize queue, vector which holds path for each iteration and 
    // vector for all visited nodes
    queue<vector<int>> q;
    vector<int> path;
    vector<bool> visited(V, false);

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

vector<int> bidir(vector<pair<int, int>> adj[], int s, int t, int V) {
    if (s == t) {
        return vector<int>(1, s);
    }

    queue<vector<int>> s_queue, t_queue;
    vector<int> s_path, t_path, path;
    vector<int> s_parent(V), t_parent(V);
    vector<bool> s_visited(V, false), t_visited(V, false);

    s_path.push_back(s);
    s_queue.push(s_path);
    s_visited[s] = true;
    s_parent[s] = -1;

    t_path.push_back(t);
    t_queue.push(t_path);
    t_visited[t] = true;
    t_parent[s] = -1;

    while (!s_queue.empty() && !t_queue.empty()) {
        s_path = s_queue.front();
        s_queue.pop();
        int s_last = s_path[s_path.size() - 1];
        
        t_path = t_queue.front();
        t_queue.pop();
        int t_last = t_path[t_path.size() - 1];

        auto s_it = adj[s_last].begin();
        auto t_it = adj[t_last].begin();
        while (s_it != adj[s_last].end() && t_it != adj[t_last].end()) {
            if (!s_visited[s_it->first]) {
                s_visited[s_it->first] = true;
                vector<int> newpath(s_path);
                newpath.push_back(s_it->first);
                s_queue.push(newpath);
            }
            if (!t_visited[t_it->first]) {
                t_visited[t_it->first] = true;
                vector<int> newpath(t_path);
                newpath.push_back(t_it->first);
                t_queue.push(newpath);
            }
            s_it++;
            t_it++;

            int intersectNode = -1;
            for (int i = 0; i < V; i++) {
                if (s_visited[i] && t_visited[i]) {
                    intersectNode = i;
                }
            }

            if (intersectNode != -1) {
                for (int i = 0; i < s_path.size(); i++) {
                    if (s_path[i] != intersectNode) {
                        path.push_back(s_path[i]);
                    }
                }
                path.push_back(intersectNode);
                for (int i = t_path.size() - 1; i >= 0; i--) {
                    if (t_path[i] != intersectNode) {
                        path.push_back(t_path[i]);
                    }
                }    
                return path;
            }
        }
    }
    return path;
}

void printGraph(vector<pair<int,int> > adj[], int V) {
    int v, w;
    for (int u = 1; u <= V; u++) {
        cout << "Node " << u << " makes an edge with \n";
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++) {
            v = it->first;
            w = it->second;
            cout << "\tNode " << v << " with edge weight = "
                 << w << "\n";
        }
        cout << "\n";
    }
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

    for (int u = 1; u <= n; u++) {
        sort(adj[u].begin(), adj[u].end());
        adj[u].erase(unique(adj[u].begin(), adj[u].end()), adj[u].end());
    }

    int weight = 0;
    vector<int> path = bfs(adj, s, t, n, &weight);
    cout << path.size() - 1 << endl;
    cout << weight << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;

    path = bidir(adj, s, t, n);
    cout << path.size() - 1 << endl;
    // cout << weight << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;

    return 0;
}
