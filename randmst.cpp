#include <iostream>
#include <cstdlib> // For atoi
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct Edge {
    int u, v;
    double weight;
    Edge(int _u, int _v, double _w) : u(_u), v(_v), weight(_w) {}
};

bool compareEdge(Edge a, Edge b) {
    return a.weight < b.weight;
}

class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if (rank[xr] < rank[yr]) {
            parent[xr] = yr;
        } else if (rank[xr] > rank[yr]) {
            parent[yr] = xr;
        } else {
            parent[yr] = xr;
            rank[xr]++;
        }
    }
};

vector<Edge> generateGraph(int n) {
    vector<Edge> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double weight = static_cast<double>(rand()) / RAND_MAX;
            edges.emplace_back(i, j, weight);
        }
    }
    return edges;
}

double kruskalsMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compareEdge);
    UnionFind uf(n);
    double totalWeight = 0;
    for (Edge& e : edges) {
        if (uf.find(e.u) != uf.find(e.v)) {
            uf.unite(e.u, e.v);
            totalWeight += e.weight;
        }
    }
    return totalWeight;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Usage: ./randmst 0 numpoints numtrials dimension" << endl;
        return 1;
    }

    int flag = atoi(argv[1]);
    int numpoints = atoi(argv[2]);
    int numtrials = atoi(argv[3]);
    int dimension = atoi(argv[4]);

    srand(static_cast<unsigned int>(time(nullptr))); // Seed random number generator

    double totalWeight = 0;
    for (int trial = 0; trial < numtrials; ++trial) {
        vector<Edge> edges = generateGraph(numpoints);
        totalWeight += kruskalsMST(numpoints, edges);
    }

    double averageWeight = totalWeight / numtrials;
    cout << "average weight: " << averageWeight << " for numpoints: " << numpoints << " over " << numtrials << " trials" << endl;

    return 0;
}
