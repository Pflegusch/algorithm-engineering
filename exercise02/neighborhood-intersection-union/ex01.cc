#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <set>

using namespace std;

void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt) {
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void printGraph(vector<pair<int, int>> adj[], int V)
{
    int v, w;
    for (int u = 1; u <= V; u++)
    {
        cout << "Node " << u << " makes an edge with \n";
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++)
        {
            v = it->first;
            w = it->second;
            cout << "\tNode " << v << " with edge weight ="
                 << w << "\n";
        }
        cout << "\n";
    }
}

int edgeCut(pair<int, vector<pair<int, int>>> part[], int V, bool weighted) {
    vector<pair<int, int>> crossings;
    int v;
    int weightedEdgeCut = 0;
    for (int u = 1; u <= V; u++) {
        for (auto it = part[u].second.begin(); it != part[u].second.end(); it++) {
            v = it->first;
            if (part[u].first != part[v].first) {
                crossings.push_back(make_pair(u, v));
                weightedEdgeCut += it->second;
            }
        }
    }

    for_each(crossings.begin(), crossings.end(), [](auto& tuple) {
        if (tuple.first < tuple.second) {
            swap(tuple.first, tuple.second);
        }
    });

    sort(crossings.begin(), crossings.end());
    crossings.erase(unique(crossings.begin(), crossings.end()),
        crossings.end());

    if (weighted) {
        return weightedEdgeCut / 2;
    } else {
        return crossings.size();
    }
}

void solution(vector<pair<int, int>> adj[], pair<int, int> vertices, int V, bool neighborhood) {
    int v1 = vertices.first;
    int v2 = vertices.second;
    vector<int> von;

    // Store neighbors in a vector
    for (auto it = adj[v1].begin(); it != adj[v1].end(); it++) {
        von.push_back(it->first);
    }
    for (auto it = adj[v2].begin(); it != adj[v2].end(); it++) {
        von.push_back(it->first);
    }

    if (neighborhood) {
        // If one needs the neigborhood, remove all duplicate entries and return the
        // neighborhood
        sort(von.begin(), von.end());
        von.erase(unique(von.begin(), von.end()), von.end());
        for (auto &i : von) {
            cout << i << " ";
        }
        cout << endl;
    } else {
        // The intersection are all duplicate entries in the neigborhood vector from above,
        // to get them, sort the vector and find all duplicates
        sort(von.begin(), von.end());
        set<int> distinct(von.begin(), von.end());
        set<int> duplicates;
        set_difference(von.begin(), von.end(), distinct.begin(), distinct.end(), 
            inserter(duplicates, duplicates.end()));
        for (auto &i : duplicates) {
            cout << i << " ";
        }
        cout << endl;
    }  
}

int main(int argc, char** argv) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> adj[m];
    
    for (int i = 0; i < 2*m; i++) {
        int src, dest, w;
        cin >> src >> dest >> w;
        addEdge(adj, src, dest, w);
    }

    pair<int, int> vertices;
    cin >> vertices.first >> vertices.second;
    assert(0 < vertices.first && vertices.first <= n);
    assert(0 < vertices.second && vertices.second <= n);

    for (int u = 1; u <= n; u++) {
        sort(adj[u].begin(), adj[u].end());
        adj[u].erase(unique(adj[u].begin(), adj[u].end()), adj[u].end());
    }

    printGraph(adj, n);
    solution(adj, vertices, n, false);
    solution(adj, vertices, n, true);

    return 0;
}
