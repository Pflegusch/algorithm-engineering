#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "bits/stdc++.h"

using namespace std;

void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt) {
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

void applyPartition(
    pair<int, vector<pair<int, int>>> part[], 
    vector<pair<int, int>> adj[], 
    int b, int n, int i) 
{
    part[i].first = b;
    part[i].second = adj[i];
}

int currentCut(pair<int, vector<pair<int, int>>> part[], int V) {
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
    // Calculate the node with the most heavy edges incident to it, putting this in S will
    // be a good start
    int cut = 0, lastAdded = 0;
    for (int u = 1; u <= n; u++) {
        int currentCut = 0;
        for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
            currentCut += it->second;
        }
        if (currentCut > cut) {
            cut = currentCut;
            lastAdded = u;
        }
    }
    
    // Apply partition, put heaviest node into S and rest alternately into S and T
    applyPartition(part, adj, 0, n, lastAdded);
    for (int u = 1; u <= n; u++) {
        if (u == lastAdded) continue;
        applyPartition(part, adj, u % 2, n, u);
    }

    // Starting from the heaviest node, always pick the edge with the smallest weight
    // and start putting the node incident to it into the other partition
    // TODO: This is not optimal, because the loop will finish once there is a node found 
    // were all node incident to it wont provide any better solution if you move them
    // to the other set - so there are nodes that wont get scanned by this
    int edge = 0;
    while (edge != adj[lastAdded].size() - 1) {
        // Always the element with the smallest edge weight after
        int currentBlock = part[adj[lastAdded][edge].first].first;
        int newBlock = (!currentBlock) ? 1 : 0;
        applyPartition(part, adj, newBlock, n, adj[lastAdded][edge].first);
        int iterCut = currentCut(part, n);

        if (iterCut < cut) {
            // If new cut doesnt increase, proceed with next smallest edge
            applyPartition(part, adj, currentBlock, n, adj[lastAdded][edge].first);
            edge++;
        } else if (iterCut == cut) {
            edge++;
        } else {
            // Move to next vertex if better solution is found
            lastAdded = adj[lastAdded][edge].first;
            edge = 0;
            cut = iterCut;
        }
    }

    // Give solution
    cout << currentCut(part, n) << endl;
    for (int u = 1; u <= n; u++) {
        if (part[u].first == 0) {
            cout << u << " ";
        }
    }
    cout << endl;
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

    // Erase duplicates and sort adj after weights to always have the smallest one at the top
    // Necessary for the above implementation to work
    for (int u = 1; u <= n; u++) {
        sort(adj[u].begin(), adj[u].end());
        adj[u].erase(unique(adj[u].begin(), adj[u].end()), adj[u].end());
        sort(adj[u].begin(), adj[u].end(), [](pair<int, int> a, pair<int, int> b) {
            return a.second < b.second;
        });
    }

    max_cut_label_propagation(adj, partition, n);

    return 0;
}
