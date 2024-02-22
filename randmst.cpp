#include <iostream>
#include <cstdlib> 
#include <vector>
#include <algorithm>
#include <cmath> 
#include <ctime> 
#include <assert.h>

using namespace std;

struct Point
{
    vector<double> coordinates; 
    Point(const vector<double> &_coordinates) : coordinates(_coordinates) {}
};

struct Edge
{
    int u, v;
    double weight;
    Edge(int _u, int _v, double _w) : u(_u), v(_v), weight(_w) {}
};

bool compareEdge(Edge a, Edge b)
{
    return a.weight < b.weight;
}

class UnionFind
{
    vector<int> parent, rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y)
    {
        int xr = find(x), yr = find(y);
        if (rank[xr] < rank[yr])
        {
            parent[xr] = yr;
        }
        else if (rank[xr] > rank[yr])
        {
            parent[yr] = xr;
        }
        else
        {
            parent[yr] = xr;
            rank[xr]++;
        }
    }
};

vector<Point> generatePoints(int n, int dimension)
{
    vector<Point> points;
    for (int i = 0; i < n; ++i)
    {
        vector<double> coordinates(dimension);
        for (int d = 0; d < dimension; ++d)
        {
            coordinates[d] = static_cast<double>(rand()) / RAND_MAX;
        }
        points.emplace_back(coordinates);
    }
    return points;
}

// Calculate Euclidean distance, generalized for multiple dimensions
double calculateDistance(const Point &a, const Point &b)
{
    double sum = 0;
    for (size_t i = 0; i < a.coordinates.size(); ++i)
    {
        sum += (a.coordinates[i] - b.coordinates[i]) * (a.coordinates[i] - b.coordinates[i]);
    }
    return sqrt(sum);
}

vector<Edge> generateGraph(int n, int dimension)
{
    vector<Edge> edges;
    if (dimension > 0)
    {
        double edgeMax = -.1 * (log2(n) - 1.4) + 1.5;
        if (dimension > 2)
        {
            edgeMax += 0.2;
        }
        if (((log2(n)) > 10) && (dimension == 2))
        {
            edgeMax = 0.15;
        }
        vector<Point> points = generatePoints(n, dimension);
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                double weight = calculateDistance(points[i], points[j]);
                if (weight < edgeMax)
                {
                    edges.emplace_back(i, j, weight);
                }
                
            }
        }
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                double weight = static_cast<double>(rand()) / RAND_MAX; // Random weight
                edges.emplace_back(i, j, weight);
            }
        }
    }
    return edges;
}

double kruskalsMST(int n, vector<Edge> &edges)
{
    sort(edges.begin(), edges.end(), compareEdge);
    UnionFind uf(n);
    double totalWeight = 0;
    int numedges = 0;
    for (Edge &e : edges)
    {
        if (uf.find(e.u) != uf.find(e.v))
        {
            uf.unite(e.u, e.v);
            numedges++;
            totalWeight += e.weight;
        }
    }
    assert(numedges == (n - 1));
    return totalWeight;
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cerr << "Usage: ./randmst 0 numpoints numtrials dimension" << endl;
        return 1;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    int numpoints = atoi(argv[2]);
    int numtrials = atoi(argv[3]);
    int dimension = atoi(argv[4]);

    double totalWeight = 0;
    for (int trial = 0; trial < numtrials; ++trial)
    {
        vector<Edge> edges = generateGraph(numpoints, dimension);
        totalWeight += kruskalsMST(numpoints, edges);
    }

    double averageWeight = totalWeight / numtrials;
    cout << averageWeight << " " << numpoints << " " << numtrials << " " << dimension << endl;

    return 0;
}
