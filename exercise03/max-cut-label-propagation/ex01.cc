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

void max_cut_label_prop(vector<pair<int, int>> adj[], 
    pair<int, vector<pair<int, int>>> part[],
    int n) 
{
    // This is too good, no 1/2 approximation
    int currentMaxWeight = 0, maxWeight = 0;
    int maxNode = 0;
    for (int u = 1; u <= n; u++) {
        for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
            currentMaxWeight += it->second;
        }
        if (currentMaxWeight > maxWeight) {
            maxWeight = currentMaxWeight;
            maxNode = u;
        }
        currentMaxWeight = 0;
    }

    // One testcase no 1/2 approximation
    maxNode = 1;
    applyPartition(part, adj, 0, n, 1);
    for (int u = 2; u <=n; u++) {
        applyPartition(part, adj, u % 2, n, u);
    }

    // Too good, all testcases fail bc of no 1/2 approximation
    // applyPartition(part, adj, 0, n, maxNode);
    // for (int u = 1; u <= n; u++) {
    //     if (u == maxNode) continue;
    //     applyPartition(part, adj, 1, n, u);
    // }

    int lastAdded = maxNode;
    int cut = currentCut(part, n);
    int edge = 0;
    while (edge != adj[lastAdded].size() - 1) {
        // Always the element with the smallest edge weight after
        int currentBlock = adj[lastAdded][edge].first;
        int newBlock = (!currentBlock) ? 1 : 0;
        applyPartition(part, adj, newBlock, n, adj[lastAdded][edge].second);
        int iterCut = currentCut(part, n);

        if (iterCut < cut) {
            // If new cut doesnt increase, proceed with next smallest edge
            applyPartition(part, adj, currentBlock, n, adj[lastAdded][edge].second);
            edge++;
        } else if (iterCut == cut) {
            edge++;
        } else {
            lastAdded = adj[lastAdded][edge].first;
            edge = 0;
            cut = iterCut;
        }
    }

    cout << currentCut(part, n) << endl;
    for (int u = 1; u <= n; u++) {
        if (part[u].first == 1) {
            cout << u << " ";
        }
    }
    cout << endl;
    // https://www.cl.cam.ac.uk/teaching/1617/AdvAlgo/maxcut.pdf
    // https://www.cs.jhu.edu/~mdinitz/classes/ApproxAlgorithms/Spring2019/Lectures/lecture5.pdf
}

void max_cut_label_propagation(vector<pair<int, int>> adj[], 
    pair<int, vector<pair<int, int>>> part[],
    int n) 
{
    // Initialize S and T with S as the first node in the graph, maybe use n with 
    // most outgoing edges here
    applyPartition(part, adj, 0, n, 7);

    // The rest is in T
    for (int u = 1; u < n; u++) {
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
                cout << cut << endl;
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

    // Erase duplicates and sort adj after weights to always have the smallest one at the top
    for (int u = 1; u <= n; u++) {
        sort(adj[u].begin(), adj[u].end());
        adj[u].erase(unique(adj[u].begin(), adj[u].end()), adj[u].end());
        sort(adj[u].begin(), adj[u].end(), [](pair<int, int> a, pair<int, int> b) {
            return a.second < b.second;
        });
    }

    //printGraph(adj, n);

    // max_cut_label_propagation(adj, partition, n);
    // cout << endl;
    max_cut_label_prop(adj, partition, n);

    return 0;
}
