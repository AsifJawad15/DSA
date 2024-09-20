#include <bits/stdc++.h>
using namespace std;


class MinHeap {
    vector<pair<int, int>> heap; // heap to store pairs of (value, key)
    unordered_map<int, int> pos; // map to store positions of keys in the heap

    // Function to maintain heap property from a given node to the root
    void heapify_up(int idx) {
        while (idx > 0 && heap[idx].first < heap[(idx - 1) / 2].first) {
            swap(pos[heap[idx].second], pos[heap[(idx - 1) / 2].second]);
            swap(heap[idx], heap[(idx - 1) / 2]);
            idx = (idx - 1) / 2;
        }
    }

    // Function to maintain heap property from a given node to the leaves
    void heapify_down(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < heap.size() && heap[left].first < heap[smallest].first)
            smallest = left;

        if (right < heap.size() && heap[right].first < heap[smallest].first)
            smallest = right;

        if (smallest != idx) {
            swap(pos[heap[idx].second], pos[heap[smallest].second]);
            swap(heap[idx], heap[smallest]);
            heapify_down(smallest);
        }
    }

public:
    // Insert a new key-value pair into the heap
    void insert(int key, int value) {
        heap.push_back({value, key});
        int idx = heap.size() - 1;
        pos[key] = idx;
        heapify_up(idx);
    }

    // Extract the minimum value from the heap
    pair<int, int> extract_min() {
        pair<int, int> min = heap.front();
        heap[0] = heap.back();
        pos[heap[0].second] = 0;
        heap.pop_back();
        pos.erase(min.second);
        heapify_down(0);
        return min;
    }

    // Decrease the value of a given key in the heap
    void decrease_key(int key, int new_value) {
        int idx = pos[key];
        heap[idx].first = new_value;
        heapify_up(idx);
    }

    // Check if the heap is empty
    bool is_empty() {
        return heap.empty();
    }

    // Check if the heap contains a given key
    bool contains(int key) {
        return pos.find(key) != pos.end();
    }
};

// Function to find the shortest path in a graph using Dijkstra's algorithm
vector<int> shortestPath(int n, vector<vector<pair<int, int>>>& adj, int start, int nd, vector<int>& dist, unordered_map<int, int>& pos) {
    MinHeap pq; // priority queue implemented as a MinHeap
    vector<int> parent(n + 1); // to store the parent of each node
    for (int i = 1; i <= n; i++)
        parent[i] = i;
    dist[start] = 0;
    pq.insert(start, 0);

    while (!pq.is_empty()) {
        pair<int, int> top = pq.extract_min(); // get the node with the minimum distance
        int node = top.second;
        int dis = top.first;

        // distance calculation step
        for (int i = 0; i < adj[node].size(); i++) {
            int adjNode = adj[node][i].first;
            int edgeWeight = adj[node][i].second;

            if (dis + edgeWeight < dist[adjNode]) {
                dist[adjNode] = dis + edgeWeight;
                if (pq.contains(adjNode))
                    pq.decrease_key(adjNode, dist[adjNode]);
                else
                    pq.insert(adjNode, dist[adjNode]);
                parent[adjNode] = node;
            }
        }
    }

    // If there's no path to the destination node
    if (dist[nd] == 1e9)
        return {-1};

    // Reconstruct the path from start to the destination node
    vector<int> path;
    int node = nd;
    while (parent[node] != node) {
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n, m;
    cin >> n >> m;
    int start;
    vector<vector<pair<int, int>>> adj(n + 1); // adjacency list to store the graph

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        if (i == 0)
            start = u;
    }

    cout << "vertex " << start << ": Distance 0" << endl;

    // Calculate shortest path from the start node to all other nodes
    for (int nd = 1; nd <= n; nd++) {
        if (nd == start) continue;

        vector<int> dist(n + 1, 1e9); // distance array initialized to infinity
        unordered_map<int, int> pos;
        vector<int> path = shortestPath(n, adj, start, nd, dist, pos);

        if (dist[nd] == 1e9) continue;

        cout << "vertex " << nd << ": ";
        cout << "Distance " << dist[nd] << endl;
    }

    return 0;
}
