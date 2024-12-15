#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int u, v, weight;
};

// Structure to represent a Disjoint Set Union (DSU) for union-find operations
struct DSU {
    vector<int> parent, rank;

    // Initialize DSU for `n` elements
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find the representative of the set containing `x` (with path compression)
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union of two sets containing `x` and `y` (by rank)
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            }
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Compare function for sorting edges by weight
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Kruskal's Algorithm to find the Minimum Spanning Tree (MST)
vector<Edge> kruskalMST(int n, vector<Edge>& edges) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareEdges);

    DSU dsu(n);
    vector<Edge> mst;  // To store the edges in the MST
    int mstWeight = 0; // Total weight of the MST

    for (const auto& edge : edges) {
        // Check if the edge forms a cycle
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            // Add edge to MST
            mst.push_back(edge);
            mstWeight += edge.weight;

            // Perform union of the sets
            dsu.unite(edge.u, edge.v);
        }
    }

    cout << "Total weight of MST: " << mstWeight << endl;
    return mst;
}

// Main function to test the implementation
int main() {
    int n = 5; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    cout << "Edges in the MST:" << endl;
    vector<Edge> mst = kruskalMST(n, edges);

    for (const auto& edge : mst) {
        cout << "(" << edge.u << ", " << edge.v << ") - Weight: " << edge.weight << endl;
    }

    return 0;
}
