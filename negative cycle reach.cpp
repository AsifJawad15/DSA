#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int V, E;
    cin >> V >> E;

    vector<vector<pair<int, int>>> adj(V);
    vector<vector<int>> reverse_adj(V);
    vector<int> dist(V, INF);
    vector<bool> inNegCycle(V, false);

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        reverse_adj[v].emplace_back(u);
    }

    dist[0] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            if (dist[u] == INF) continue;
            for (auto& edge : adj[u]) {
                int v = edge.first, w = edge.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    for (int u = 0; u < V; ++u) {
        if (dist[u] == INF) continue;
        for (auto& edge : adj[u]) {
            int v = edge.first, w = edge.second;
            if (dist[u] + w < dist[v]) {
                inNegCycle[u] = true;
                inNegCycle[v] = true;
            }
        }
    }

    vector<bool> reachable(V, false);

    queue<int> q;

    for (int i = 0; i < V; ++i) {
        if (inNegCycle[i]) {
            q.push(i);
            reachable[i] = true;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : reverse_adj[u]) {
            if (!reachable[v]) {
                reachable[v] = true;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < V; ++i) {
        if (reachable[i]) {
            cout << i << " ";
        }
    }

    return 0;
}
