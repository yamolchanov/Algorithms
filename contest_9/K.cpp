#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

const long long cInf = 100000000000;

struct Edge {
  int to;
  int rev;
  int cap;
  long long cost;
};

class Graph {
 public:
  explicit Graph(int n) : n_(n), g_(n + 1) {}

  void AddEdge(int u, int v, int cap, long long cost) {
    g_[u].push_back({v, static_cast<int>(g_[v].size()), cap, cost});
    g_[v].push_back({u, static_cast<int>(g_[u].size() - 1), 0, -cost});
  }

  long long MinCostMaxFlow(int s, int t) {
    long long total_cost = 0;
    std::vector<long long> pot(n_ + 1, 0);
    std::vector<long long> dist(n_ + 1);
    std::vector<int> pv(n_ + 1);
    std::vector<int> pe(n_ + 1);

    while (true) {
      dist.assign(n_ + 1, cInf);
      dist[s] = 0;

      std::priority_queue<std::pair<long long, int>,
                          std::vector<std::pair<long long, int>>,
                          std::greater<>>
          pq;
      pq.push({0, s});

      while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) {
          continue;
        }

        for (int i = 0; i < static_cast<int>(g_[u].size()); ++i) {
          Edge& e = g_[u][i];
          if (e.cap > 0) {
            long long reduced_cost = e.cost + pot[u] - pot[e.to];
            if (dist[u] + reduced_cost < dist[e.to]) {
              dist[e.to] = dist[u] + reduced_cost;
              pv[e.to] = u;
              pe[e.to] = i;
              pq.push({dist[e.to], e.to});
            }
          }
        }
      }

      if (dist[t] == cInf) {
        break;
      }

      for (int i = 1; i <= n_; ++i) {
        if (dist[i] < cInf) {
          pot[i] += dist[i];
        }
      }

      long long addf = std::numeric_limits<long long>::max();
      for (int v = t; v != s; v = pv[v]) {
        Edge& e = g_[pv[v]][pe[v]];
        addf = std::min(addf, (long long)e.cap);
      }

      total_cost += addf * pot[t];
      for (int v = t; v != s; v = pv[v]) {
        Edge& e = g_[pv[v]][pe[v]];
        e.cap -= addf;
        g_[v][e.rev].cap += addf;
      }
    }

    return total_cost;
  }

 private:
  int n_;
  std::vector<std::vector<Edge>> g_;
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
    long long w;
    std::cin >> u >> v >> c >> w;
    graph.AddEdge(u, v, c, w);
  }

  int s = 1;
  int t = n;
  std::cout << graph.MinCostMaxFlow(s, t) << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Solve();
}