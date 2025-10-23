#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int src, dest, weight;
};
void bellmanFord(vector<Edge> &edges, int V, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    for (int i = 0; i < V - 1; i++) {
        for (auto &e : edges) {
            if (dist[e.src] != INT_MAX && dist[e.src] + e.weight < dist[e.dest])
                dist[e.dest] = dist[e.src] + e.weight;
        }
    }

    bool attack = false;
    for (auto &e : edges) {
        if (dist[e.src] != INT_MAX && dist[e.src] + e.weight < dist[e.dest]) {
            attack = true;
            break;
        }
    }

    if (attack)
        cout << "\nAlert: Suspicious negative cycle detected (Possible Attack Loop)!\n";
    else
        cout << "\nNo anomalies detected in routing paths\n";
}
void dfsUtil(int v, vector<vector<int>> &adj, vector<bool> &visited) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) dfsUtil(u, adj, visited);
    }
}

void checkConnectivity(vector<vector<int>> &adj, int V) {
    vector<bool> visited(V, false);
    dfsUtil(0, adj, visited);

    bool allConnected = true;
    for (bool v : visited)
        if (!v) allConnected = false;

    if (allConnected)
        cout << "All devices are connected (No isolation detected).\n";
    else
        cout << "Vulnerability: Some devices are disconnected from the network!\n";
}
struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (x != parent[x]) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) parent[x] = y;
        else if (rank[x] > rank[y]) parent[y] = x;
        else { parent[y] = x; rank[x]++; }
    }
};

void kruskal(vector<Edge> &edges, int V) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    DSU dsu(V);
    vector<Edge> mst;
    int cost = 0;

    for (auto &e : edges) {
        if (dsu.find(e.src) != dsu.find(e.dest)) {
            dsu.unite(e.src, e.dest);
            mst.push_back(e);
            cost += e.weight;
        }
    }

    cout << "\n Secure Minimal Network Design (MST):\n";
    for (auto &e : mst)
        cout << "  " << e.src << " -- " << e.dest << "  (Weight: " << e.weight << ")\n";
    cout << "Total Secure Network Cost: " << cost << endl;
}
int main() {
    int V, E;
    cout << " Network Attack Detection System (Graph-Based)\n";
    cout << "Enter number of devices (nodes): ";
    cin >> V;
    cout << "Enter number of connections (edges): ";
    cin >> E;

    vector<Edge> edges(E);
    vector<vector<int>> adj(V);

    cout << "\nEnter connections (src dest weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
        adj[edges[i].src].push_back(edges[i].dest);
        adj[edges[i].dest].push_back(edges[i].src);
    }
    bellmanFord(edges, V, 0);
    checkConnectivity(adj, V);
    kruskal(edges, V);

    return 0;
}