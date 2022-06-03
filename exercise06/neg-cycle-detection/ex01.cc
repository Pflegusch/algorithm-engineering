#include <bits/stdc++.h>
using namespace std;

vector<int> vis;

// Structure to represent a weighted
// edge in graph
struct Edge
{
    int src, dest, weight;
};

// Structure to represent a directed
// and weighted graph
struct Graph
{

    // V -> Number of vertices,
    // E -> Number of edges
    int V, E;

    // Graph is represented as an
    // array of edges
    struct Edge *edge;
};

// Creates a new graph with V vertices
// and E edges
struct Graph *createGraph(int V, int E)
{
    struct Graph *graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[graph->E];
    return graph;
}

// Function runs Bellman-Ford algorithm
// and prints negative cycle(if present)
void NegCycleBellmanFord(struct Graph *graph,
                         int src)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];
    int parent[V];

    // Initialize distances from src
    // to all other vertices as INFINITE
    // and all parent as -1
    for (int i = 0; i < V; i++)
    {

        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0;
    vis[src] = 0;
    // Relax all edges |V| - 1 times.
    bool flg = true;
    for (int i = 1; i <= V - 1; i++)
    {
        if (flg == false)
            break;
        flg = false;
        for (int j = 0; j < E; j++)
        {

            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                flg = true;
                vis[v] = 1;
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    // Check for negative-weight cycles
    int C = -1;
    for (int i = 0; i < E; i++)
    {

        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {

            // Store one of the vertex of
            // the negative weight cycle
            C = v;
            break;
        }
    }

    if (C != -1)
    {

        for (int i = 0; i < V; i++)
            C = parent[C];

        // To store the cycle vertex
        vector<int> cycle;
        for (int v = C;; v = parent[v])
        {

            cycle.push_back(v);
            if (v == C && cycle.size() > 1)
                break;
        }

        // Reverse cycle[]
        reverse(cycle.begin(), cycle.end());

        // Printing the negative cycle
        cout << cycle.size() - 1 << endl;
        for (int v : cycle)
            cout << v << ' ';
        cout << endl;
        exit(0);
    }
}

// Driver Code
int main(int argc, char **argv)
{
    int n, m;
    cin >> n >> m;
    struct Graph *graph = createGraph(n, 2 * m);
    vis.resize(n, 0);

    for (int i = 0; i < 2 * m; i++)
    {
        int src, dest, w;
        cin >> src >> dest >> w;
        graph->edge[i].src = src;
        graph->edge[i].dest = dest;
        graph->edge[i].weight = w;
    }

    NegCycleBellmanFord(graph, 1);
    return 0;
}