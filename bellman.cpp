#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int u, v, weight;
};



void printCycle(int v, const vector<int>& parent) {
    vector<int> cycle;
    int current = v;

    while (true) {
        cycle.push_back(current);
        current = parent[current];
        if (find(cycle.begin(), cycle.end(), current) != cycle.end()) {
            cycle.push_back(current);
            break;
        }
    }

    reverse(cycle.begin(), cycle.end());

    for (int i = 0; i < cycle.size(); ++i) {
        cout << cycle[i] << " ";
        if (i > 0 && cycle[i] == cycle[0]) break;
    }
    cout << endl;
}

void bellmanFord(int n, int m, int source, const vector<Edge>& edges) {
    vector<int> dist(n + 1, 1e9);
    vector<int> parent(n + 1, -1);
    dist[source] = 0;

    for (int i = 1; i <= n - 1; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != 1e9 && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
                parent[edge.v] = edge.u;
            }
        }
    }

    for (const auto& edge : edges) {
        if (dist[edge.u] != 1e9 && dist[edge.u] + edge.weight < dist[edge.v]) {
            cout << "Negative cycle detected!" << endl;

            vector<bool> visited(n + 1, false);
            int cycleStart = edge.v;


            for (int i = 1; i <= n; ++i) {
                cycleStart = parent[cycleStart];
            }

            printCycle(cycleStart, parent);
            return;
        }
    }


    if (dist[n] == 1e9) {
        cout << "No path from node 1 to node " << n << endl;
    } else {
        cout << "Shortest distance from node 1 to node " << n << " is: " << dist[n] << endl;
    }
}

int main() {


    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }


    bellmanFord(n, m, 1, edges);

    return 0;
}

