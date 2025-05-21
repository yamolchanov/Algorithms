#include <algorithm>
#include <iostream>
#include <vector>

const int cInf = 100000000;
const int cJoke = 100000;

struct Edge {
  int u;
  int v;
  int w;
};

class Graph {
public:
  Graph(int n) : n_(n) {}
  void AddEdge(int u, int v, int w) { edges_.push_back({u, v, w}); }
  const std::vector<Edge>& GetEdges() const { return edges_; }
  int Size() const { return n_; }

private:
  int n_;
  std::vector<Edge> edges_;
};

void Solve(const Graph& g) {
  int n = g.Size();
  std::vector<int> dist(n, cInf);
  std::vector<int> p(n, -1);
  dist[0] = 0;
  int x = -1;

  const std::vector<Edge>& edges = g.GetEdges();
  for (int i = 0; i < n; ++i) {
    x = -1;
    for (const auto& edge : edges) {
      int u = edge.u;
      int v = edge.v;
      int w = edge.w;
      if (dist[v] > dist[u] + w) {
        dist[v] = std::max(-cInf, dist[u] + w);
        p[v] = u;
        x = v;
      }
    }
  }

  if (x == -1) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    std::vector<int> cycle;
    int y = x;

    for (int i = 0; i < n; ++i) {
      y = p[y];
    }

    for (int cur = y;; cur = p[cur]) {
      cycle.push_back(cur);
      if (cur == y && cycle.size() > 1) {
        break;
      }
    }

    std::reverse(cycle.begin(), cycle.end());

    std::cout << cycle.size() << "\n";
    for (int i = 0; i < static_cast<int>(cycle.size()); ++i) {
      std::cout << cycle[i] + 1;
      if (i != static_cast<int>(cycle.size()) - 1) {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;

  Graph g(n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int w;
      std::cin >> w;
      if (w != cJoke) {
        g.AddEdge(i, j, w);
      }
    }
  }

  Solve(g);
}