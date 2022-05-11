#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;

void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt) {
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

int degree(vector<pair<int, int>> adj[], int V, bool maximum) {
    int result;
    if (maximum) {
        result = 0;
    } else {
        result = INT32_MAX;
    }
        
    for (int u = 1; u <= V; u++) {
        if (maximum) {
            result = max(result, (int)adj[u].size());
        } else {
            result = min(result, (int)adj[u].size());
        }        
    }
    return result;
}

int weightedDegree(vector<pair<int, int>> adj[], int V, bool maximum) {
    int result;
    if (maximum) {
        result = 0;
    } else {
        result = INT32_MAX;
    }
        
    for (int u = 1; u <= V; u++) {
        int current = 0;
        for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
            current += it->second;
        }
        if (maximum) {
            result = max(result, current);
        } else {
            result = min(result, current);
        }
    }
    return result;
}

int totalWeight(vector<pair<int, int>> adj[], int V) {
    int result = 0;
    for (int u = 1; u <= V; u++) {
        for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
            result += it->second;
        }
    }
    return result / 2;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> adj[m];
    
    for (int i = 0; i < 2*m; i++) {
        int src, dest, w;
        cin >> src >> dest >> w;
        addEdge(adj, src, dest, w);
    }

    for (int u = 1; u <= n; u++) {
        sort(adj[u].begin(), adj[u].end());
        adj[u].erase(unique(adj[u].begin(), adj[u].end()), adj[u].end());
    }

    cout << degree(adj, n, true) << endl;
    cout << degree(adj, n, false) << endl;
    cout << weightedDegree(adj, n, true) << endl;
    cout << weightedDegree(adj, n, false) << endl;
    cout << totalWeight(adj, n) << endl;

    return 0;
}
