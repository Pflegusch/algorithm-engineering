#include <bits/stdc++.h>

using namespace std;

int maxColor = 0;

struct custom_comparator
{
    bool operator()(const std::pair<int, int> &a,
                    const std::pair<int, int> &b) const
    {
        return less_comparator(std::minmax(a.first, a.second),
                               std::minmax(b.first, b.second));
    }

    std::less<std::pair<int, int>> less_comparator;
};

void colorEdges(int ptr, vector<vector<pair<int, int>>> &gra,
                vector<int> &edgeColors, bool isVisited[])
{
    queue<int> q;
    int c = 0;

    unordered_set<int> colored;

    if (isVisited[ptr])
        return;

    // Mark the current node visited
    isVisited[ptr] = 1;

    // Traverse all edges of current vertex
    for (long unsigned int i = 0; i < gra[ptr].size(); i++)
    {
        // if already colored, insert it into the set
        if (edgeColors[gra[ptr][i].second] != -1)
            colored.insert(edgeColors[gra[ptr][i].second]);
    }

    for (long unsigned int i = 0; i < gra[ptr].size(); i++)
    {
        // if not visited, inset into the queue
        if (!isVisited[gra[ptr][i].first])
            q.push(gra[ptr][i].first);

        if (edgeColors[gra[ptr][i].second] == -1)
        {
            // if col vector -> negative
            while (colored.find(c) != colored.end())

                // increment the color
                c++;

            // copy it in the vector
            edgeColors[gra[ptr][i].second] = c;

            // then add it to the set
            colored.insert(c);
            c++;
            if (c > maxColor)
            {
                maxColor = c;
            }
        }
    }

    // while queue's not empty
    while (!q.empty())
    {
        int temp = q.front();
        q.pop();

        colorEdges(temp, gra, edgeColors, isVisited);
    }

    return;
}

// Driver Function
int main()
{
    // declaring vector of vector of pairs, to define Graph
    vector<vector<pair<int, int>>> gra;

    vector<int> edgeColors;

    bool isVisited[100000] = {0};

    // Enter the Number of Vertices
    // and the number of edges
    int ver, edge;
    cin >> ver >> edge;

    gra.resize(ver);
    edgeColors.resize(edge, -1);

    vector<pair<int, int>> edges;
    for (int i = 0; i < 2 * edge; i++)
    {
        int src, dest, w;
        cin >> src >> dest >> w;
        src--;
        dest--;

        edges.push_back(make_pair(src, dest));
    }

    set<pair<int, int>, custom_comparator> unique;

    for (const pair<int, int> &p : edges)
    {
        unique.insert(p);
    }

    int i = 0;
    for (auto &p : unique)
    {
        gra[p.first].push_back(make_pair(p.second, i));
        gra[p.second].push_back(make_pair(p.first, i));
        i++;
    }

    colorEdges(0, gra, edgeColors, isVisited);

    cout << maxColor << endl;
    i = 0;
    for (auto &p : unique)
    {
        cout << p.first + 1 << " " << p.second + 1 << " " << edgeColors[i] + 1 << endl;
        i++;
    }

    return 0;
}

// 5
// 1 2 1
// 1 3 2
// 1 7 3
// 2 3 2 -> 2 3 3
// 2 4 3 -> 2 4 4
// 2 5 4 -> 2 5 2
// 3 4 1
// 3 5 3 -> 3 5 4
// 4 5 2 -> 4 5 3
// 4 6 4 -> 4 6 2
// 4 7 5
// 6 7 1