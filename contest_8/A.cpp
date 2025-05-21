#include <iostream>
#include <set>
#include <vector>

const long long cNot = 2009000999;

class Graph {
public:
  Graph(int n) : n_(n), g_(n) {}

  void AddEdge(int x, int y, int w) {
    g_[x].emplace_back(y, w);
    g_[y].emplace_back(x, w);
  }

  std::vector<int> Dijkstra(int s) {
    std::vector<int> d(n_, cNot);
    std::set<std::pair<int, int>> q;
    d[s] = 0;
    for (int i = 0; i < n_; ++i) {
      q.insert({d[i], i});
    }
    while (!q.empty()) {
      int v = q.begin()->second;
      q.erase(q.begin());

      for (auto& [to, len] : g_[v]) {
        if (len != -1 && d[v] + len < d[to]) {
          q.erase({d[to], to});
          d[to] = d[v] + len;
          q.insert({d[to], to});
        }
      }
    }
    return d;
  }

private:
  int n_;
  std::vector<std::vector<std::pair<int, int>>> g_;
};

void Solve() {
  int t;
  std::cin >> t;
  while (t > 0) {
    int n;
    int m;
    int s;
    std::cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
      int x;
      int y;
      int w;
      std::cin >> x >> y >> w;
      graph.AddEdge(x, y, w);
    }
    std::cin >> s;
    std::vector<int> distances = graph.Dijkstra(s);
    for (int dist : distances) {
      std::cout << dist << " ";
    }
    std::cout << "\n";
    t--;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Solve();
}