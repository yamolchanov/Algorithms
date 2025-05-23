#include <algorithm>
#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int> parent_;
  std::vector<int> rank_;

 public:
  DSU(int n) : parent_(n), rank_(n, 1) {
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  int Find(int u) {
    while (u != parent_[u]) {
      u = parent_[u];
    }
    return u;
  }

  bool Unite(int u, int v) {
    u = Find(u);
    v = Find(v);
    if (u == v) {
      return false;
    }
    if (rank_[u] < rank_[v]) {
      std::swap(u, v);
    }
    parent_[v] = u;
    if (rank_[u] == rank_[v]) {
      rank_[u]++;
    }
    return true;
  }
};

class Graph {
 private:
  struct Edge {
    int u;
    int v;
    int weight;

    Edge(int first, int second, int w) : u(first), v(second), weight(w) {}

    static bool CompareEdges(const Edge& a, const Edge& b) {
      return a.weight < b.weight;
    }
  };

  int vertex_count_;
  std::vector<Edge> edges_;

 public:
  Graph(int n) : vertex_count_(n) {}
  void AddEdge(int u, int v, int weight) {
    edges_.emplace_back(u - 1, v - 1, weight);
  }

  long long FindMST() {
    std::sort(edges_.begin(), edges_.end(), Edge::CompareEdges);
    DSU dsu(vertex_count_);
    long long total_weight = 0;
    for (const auto& edge : edges_) {
      if (dsu.Unite(edge.u, edge.v)) {
        total_weight += edge.weight;
      }
    }
    return total_weight;
  }
};

void Solve() {
  int n;
  int m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    int c;
    std::cin >> u >> v >> c;
    graph.AddEdge(u, v, c);
  }
  std::cout << graph.FindMST() << '\n';
}

int main() { Solve(); }