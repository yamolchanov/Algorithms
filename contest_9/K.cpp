#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

const long long cInf = 1e11;

struct Edge {
  int to;
  int rev;
  int cap;
  long long cost;
};

class Graph {
 public:
  explicit Graph(int n) : adj_(n + 1) {}

  void AddEdge(int u, int v, int cap, long long cost) {
    adj_[u].push_back({v, static_cast<int>(adj_[v].size()), cap, cost});
    adj_[v].push_back({u, static_cast<int>(adj_[u].size() - 1), 0, -cost});
  }

  std::vector<std::vector<Edge>>& GetAdjacencyList() { return adj_; }

 private:
  std::vector<std::vector<Edge>> adj_;
};

class MinCostMaxFlow {
 public:
  MinCostMaxFlow(Graph& graph, int source, int sink)
      : g_(graph.GetAdjacencyList()),
        n_(static_cast<int>(g_.size()) - 1),
        s_(source),
        t_(sink),
        pot_(n_ + 1, 0),
        dist_(n_ + 1),
        pv_(n_ + 1),
        pe_(n_ + 1) {}

  long long Run() {
    long long total_cost = 0;
    while (Dijkstra()) {
      UpdatePotentials();
      long long flow = Find();
      total_cost += flow * pot_[t_];
      Flow(flow);
    }
    return total_cost;
  }

 private:
  std::vector<std::vector<Edge>>& g_;
  int n_;
  int s_;
  int t_;
  std::vector<long long> pot_;
  std::vector<long long> dist_;
  std::vector<int> pv_;
  std::vector<int> pe_;

  bool Dijkstra() {
    dist_.assign(n_ + 1, cInf);
    dist_[s_] = 0;
    using P = std::pair<long long, int>;
    std::priority_queue<P, std::vector<P>, std::greater<>> pq;
    pq.push({0, s_});

    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (d > dist_[u]) {
        continue;
      }
      for (int i = 0; i < static_cast<int>(g_[u].size()); i++) {
        auto& e = g_[u][i];
        if (e.cap > 0) {
          long long reduced_cost = e.cost + pot_[u] - pot_[e.to];
          if (dist_[u] + reduced_cost < dist_[e.to]) {
            dist_[e.to] = dist_[u] + reduced_cost;
            pv_[e.to] = u;
            pe_[e.to] = i;
            pq.push({dist_[e.to], e.to});
          }
        }
      }
    }
    return dist_[t_] != cInf;
  }

  void UpdatePotentials() {
    for (int i = 1; i <= n_; i++) {
      if (dist_[i] < cInf) {
        pot_[i] += dist_[i];
      }
    }
  }

  long long Find() {
    long long addf = std::numeric_limits<long long>::max();
    for (int v = t_; v != s_; v = pv_[v]) {
      auto& e = g_[pv_[v]][pe_[v]];
      addf = std::min(addf, (long long)e.cap);
    }
    return addf;
  }

  void Flow(long long flow) {
    for (int v = t_; v != s_; v = pv_[v]) {
      int u = pv_[v];
      int idx = pe_[v];
      g_[u][idx].cap -= flow;
      g_[v][g_[u][idx].rev].cap += flow;
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; i++) {
    int u;
    int v;
    int c;
    long long w;
    std::cin >> u >> v >> c >> w;
    graph.AddEdge(u, v, c, w);
  }
  MinCostMaxFlow solver(graph, 1, n);
  std::cout << solver.Run() << "\n";
}