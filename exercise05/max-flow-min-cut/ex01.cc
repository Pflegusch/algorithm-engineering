#include <bits/stdc++.h>

using namespace std;

struct Edge
{
    int v;
    int flow;
    int C;
    size_t rev;
};

class Graph
{
    int V;
    vector<Edge> *adj;
    int *level;

public:
    Graph(int V)
    {
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }

    // add edge to the graph
    void addEdge(int u, int v, int C)
    {
        // Forward edge : 0 flow and C capacity
        Edge a{v, 0, C, adj[v].size()};

        // Back edge : 0 flow and 0 capacity
        Edge b{u, 0, 0, adj[u].size()};

        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }

    bool BFS(int s, int t);
    int sendFlow(int s, int flow, int t, int ptr[]);
    void DinicMaxflow(int s, int t);
};

// Finds if more flow can be sent from s to t.
// Also assigns levels to nodes.
bool Graph::BFS(int s, int t)
{
    level[0] = -2;
    for (int i = 1; i < V; i++)
        level[i] = -1;

    level[s] = 0;

    list<int> q;
    q.push_back(s);

    vector<Edge>::iterator i;
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++)
        {
            Edge &e = *i;
            if (level[e.v] < 0 && e.flow < e.C)
            {
                level[e.v] = level[u] + 1;
                q.push_back(e.v);
            }
        }
    }

    return level[t] < 0 ? false : true;
}

int Graph::sendFlow(int u, int flow, int t, int start[])
{
    // Sink reached
    if (u == t)
        return flow;

    // Traverse all adjacent edges one -by - one.
    while (start[u] < adj[u].size())
    {
        // Pick next edge from adjacency list of u
        Edge &e = adj[u][start[u]];

        if (level[e.v] == level[u] + 1 && e.flow < e.C)
        {
            // find minimum flow from u to t
            int curr_flow = min(flow, e.C - e.flow);

            int temp_flow = sendFlow(e.v, curr_flow, t, start);

            // flow is greater than zero
            if (temp_flow > 0)
            {
                e.flow += temp_flow;
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
        start[u]++;
    }

    return 0;
}

// Returns maximum flow in graph
void Graph::DinicMaxflow(int s, int t)
{
    int total = 0; // Initialize result

    while (BFS(s, t))
    {
        int *start = new int[V + 1]{0};

        // while flow is not zero in graph from S to D
        while (int flow = sendFlow(s, INT_MAX, t, start))
        {
            total += flow;
        }
    }

    // return maximum flow
    cout << total << endl;

    // return set
    for (int i = 1; i < V; i++)
    {
        if (level[i] != -1)
            cout << i << " ";
    }
    cout << endl;
}

// Driver Code
int main()
{
    int n, m, w, s, t;
    cin >> n >> m;
    Graph g(n + 1);

    for (int i = 0; i < 2 * m; i++)
    {
        int src, dest, w;
        cin >> src >> dest >> w;
        g.addEdge(src, dest, w);
    }

    cin >> s >> t;
    g.DinicMaxflow(s, t);

    return 0;
}
