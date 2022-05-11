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

void applyPartition(
    pair<int, vector<pair<int, int>>> part[], 
    vector<pair<int, int>> adj[], 
    int b, int n, int i) 
{
    part[i].first = b;
    part[i].second = adj[i];
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

double partitionBalance(vector<pair<int, int>> weightedBlocks, int V, int k) {
    double heaviest = 0;
    for (int i = 0; i < weightedBlocks.size(); i++) {
        if (weightedBlocks[heaviest].second < weightedBlocks[i].second) {
            heaviest = weightedBlocks[i].first;
        }
    }

    return weightedBlocks[heaviest].second / ((double)V / (double)k);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> adj[m];
    pair<int, vector<pair<int, int>>> partition[n + 1];
    
    for (int i = 0; i < 2*m; i++) {
        int src, dest, w;
        cin >> src >> dest >> w;
        addEdge(adj, src, dest, w);
    }

    vector<pair<int, int>> blockWeights(k);
    for (int i = 1; i <= n; i++) {
        int b;
        cin >> b;
        assert(0 <= b < k);
        blockWeights[b].first = b;
        blockWeights[b].second++;
        applyPartition(partition, adj, b, n, i);
    }

    for (int u = 1; u <= n; u++) {
        sort(partition[u].second.begin(), partition[u].second.end());
        partition[u].second.erase(unique(partition[u].second.begin(), 
            partition[u].second.end()), partition[u].second.end());
    }

    cout << edgeCut(partition, n, false) << endl;
    cout << edgeCut(partition, n, true) << endl;
    cout << partitionBalance(blockWeights, n, k) << endl;

    return 0;
}
