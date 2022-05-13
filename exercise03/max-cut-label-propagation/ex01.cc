#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "bits/stdc++.h"

using namespace std;

inline void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt) {
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void printGraph(vector<pair<int,int>> adj[], int V) {
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

inline void applyPartition(
    pair<int, vector<pair<int, int>>> part[], 
    vector<pair<int, int>> adj[], 
    int b, int n, int i) 
{
    part[i].first = b;
    part[i].second = adj[i];
}

inline int currentCut(pair<int, vector<pair<int, int>>> part[], int V) {
    int weightedEdgeCut = 0;
    for (int u = 1; u <= V; u++) {
        for (auto it = part[u].second.begin(); it != part[u].second.end(); it++) {
            if (part[u].first != part[it->first].first) {
                weightedEdgeCut += it->second;
            }
        }
    }

    return weightedEdgeCut / 2;
}

void max_cut_label_propagation(vector<pair<int, int>> adj[], 
    pair<int, vector<pair<int, int>>> part[],
    int n) 
{
    // Initialize S and T with S as the first node in the graph
    applyPartition(part, adj, 0, n, 1);

    // The rest is in T
    for (int u = 2; u <= n; u++) {
        applyPartition(part, adj, 1, n, u);
    }

    // Rounds of label propagation
    int failed = 0;
    int cut = 0;
    while (true) {
        for (int u = 1; u <= n; u++) {
            int currentBlock = part[u].first;
            int newBlock = (currentBlock == 0) ? 1 : 0;
            applyPartition(part, adj, newBlock, n, u);
            int roundCut = currentCut(part, n);
            if (roundCut <= cut) {
                failed++;
                applyPartition(part, adj, currentBlock, n, u);
            } else {
                cut = roundCut;
            }
            if (failed == n) {
                cout << cut / 2 << endl;
                for (int u = 1; u <= n; u++) {
                    if (part[u].first == 1) {
                        cout << u << " ";
                    }
                }
                cout << endl;
                return;
            }
        }
        failed = 0;
    }
}

int main(int argc, char** argv) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> adj[m];
    pair<int, vector<pair<int, int>>> partition[n + 1];
    
    for (int i = 0; i < 2*m; i++) {
        int src, dest, w;
        cin >> src >> dest >> w;
        addEdge(adj, src, dest, w);
    }

    max_cut_label_propagation(adj, partition, n);

    return 0;
}
