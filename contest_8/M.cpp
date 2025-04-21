#include <algorithm>
#include <iostream>
#include <vector>

struct DSU {
  std::vector<int> parent;
  std::vector<int> rank;

  DSU(int n) : parent(n), rank(n, 1) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int Evristika(int u) {
    while (u != parent[u]) {
      u = parent[u];
    }
    return u;
  }

  bool Conn(int u, int v) {
    u = Evristika(u);
    v = Evristika(v);
    if (u == v) {
      return false;
    }
    if (rank[u] < rank[v]) {
      std::swap(u, v);
    }
    parent[v] = u;
    if (rank[u] == rank[v]) {
      rank[u]++;
    }
    return true;
  }
};

struct Edge {
  int u;
  int v;
  int c;
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<Edge> edges(m);
  for (auto& e : edges) {
    std::cin >> e.u >> e.v >> e.c;
  }
  std::sort(edges.begin(), edges.end(),
            [](const Edge& a, const Edge& b) { return a.c < b.c; });
  DSU dsu(n);
  long long weight = 0;
  for (auto& e : edges) {
    if (dsu.Conn(e.u - 1, e.v - 1)) {
      weight += e.c;
    }
  }
  std::cout << weight << '\n';
}
