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

void AddEdge(int u, int v, int cap, long long cost,
             std::vector<std::vector<Edge>>& g) {
  g[u].push_back({v, static_cast<int>(g[v].size()), cap, cost});
  g[v].push_back({u, static_cast<int>(g[u].size() - 1), 0, -cost});
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<std::vector<Edge>> g(n + 1);

  for (int i = 0; i < m; i++) {
    int u;
    int v;
    int c;
    long long w;
    std::cin >> u >> v >> c >> w;
    AddEdge(u, v, c, w, g);
  }

  int s = 1;
  int t = n;
  long long total_cost = 0;

  std::vector<long long> pot(n + 1, 0);
  std::vector<long long> dist(n + 1);
  std::vector<int> pv(n + 1);
  std::vector<int> pe(n + 1);

  while (true) {
    dist.assign(n + 1, cInf);
    dist[s] = 0;

    std::priority_queue<std::pair<long long, int>,
                        std::vector<std::pair<long long, int>>,
                        std::greater<std::pair<long long, int>>>
        pq;
    pq.push({0, s});

    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();

      if (d > dist[u]) {
        continue;
      }

      for (int i = 0; i < static_cast<int>(g[u].size()); i++) {
        auto& e = g[u][i];
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
    for (int i = 1; i <= n; i++) {
      if (dist[i] < cInf) {
        pot[i] += dist[i];
      }
    }
    long long addf = std::numeric_limits<long long>::max();
    for (int v = t; v != s; v = pv[v]) {
      auto& e = g[pv[v]][pe[v]];
      addf = std::min(addf, (long long)e.cap);
    }

    total_cost += addf * pot[t];
    for (int v = t; v != s; v = pv[v]) {
      int u = pv[v];
      int edge_idx = pe[v];
      g[u][edge_idx].cap -= addf;
      g[v][g[u][edge_idx].rev].cap += addf;
    }
  }
  std::cout << total_cost << "\n";
  return 0;
}
