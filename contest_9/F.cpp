#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int cInf = 10000001;

struct Edge {
  int to;
  int capacity;
  int flow;
  int reverse;
  int index;
  Edge(int t, int cap, int f, int rev_idx, int orig_idx)
      : to(t), capacity(cap), flow(f), reverse(rev_idx), index(orig_idx) {}
};

class Graph {
 public:
  Graph(int n) : n_(n) {
    graph_.resize(n_ + 1);
    visited_.resize(n_ + 1);
    parent_vertex_.resize(n_ + 1);
    parent_edge_index_.resize(n_ + 1);
  }

  void AddEdge(int u, int v, int capacity, int index) {
    graph_[u].emplace_back(v, capacity, 0, (int)graph_[v].size(), index);
    graph_[v].emplace_back(u, capacity, 0, (int)graph_[u].size() - 1, index);
  }

  long long MaxFlow(int s, int t) {
    long long total_flow = 0;
    while (BFS(s, t)) {
      int path_flow = cInf;
      for (int v = t; v != s; v = parent_vertex_[v]) {
        int u = parent_vertex_[v];
        int edge_idx = parent_edge_index_[v];
        path_flow = std::min(
            path_flow, graph_[u][edge_idx].capacity - graph_[u][edge_idx].flow);
      }
      for (int v = t; v != s; v = parent_vertex_[v]) {
        int u = parent_vertex_[v];
        int edge_idx = parent_edge_index_[v];
        graph_[u][edge_idx].flow += path_flow;
        int rev = graph_[u][edge_idx].reverse;
        graph_[v][rev].flow -= path_flow;
      }
      total_flow += path_flow;
    }
    return total_flow;
  }

  void FindReachableFromSource(int s) {
    std::fill(visited_.begin(), visited_.end(), false);
    std::queue<int> q;
    q.push(s);
    visited_[s] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (const auto& edge : graph_[u]) {
        if (!visited_[edge.to] && edge.capacity - edge.flow > 0) {
          visited_[edge.to] = true;
          q.push(edge.to);
        }
      }
    }
  }

  std::vector<int> GetMinCutEdges() const {
    std::vector<int> cut_edges;
    for (int u = 1; u <= n_; ++u) {
      if (visited_[u]) {
        for (const auto& edge : graph_[u]) {
          if (!visited_[edge.to]) {
            cut_edges.push_back(edge.index);
          }
        }
      }
    }
    std::sort(cut_edges.begin(), cut_edges.end());
    return cut_edges;
  }

 private:
  int n_;
  std::vector<std::vector<Edge>> graph_;
  std::vector<bool> visited_;
  std::vector<int> parent_vertex_;
  std::vector<int> parent_edge_index_;

  bool BFS(int s, int t) {
    std::fill(visited_.begin(), visited_.end(), false);
    std::fill(parent_vertex_.begin(), parent_vertex_.end(), -1);
    std::fill(parent_edge_index_.begin(), parent_edge_index_.end(), -1);
    std::queue<int> q;
    q.push(s);
    visited_[s] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (size_t i = 0; i < graph_[u].size(); ++i) {
        const auto& e = graph_[u][i];
        if (!visited_[e.to] && e.capacity - e.flow > 0) {
          visited_[e.to] = true;
          parent_vertex_[e.to] = u;
          parent_edge_index_[e.to] = i;
          q.push(e.to);
        }
      }
    }
    return visited_[t];
  }
};

class Shell {
 public:
  static void Start() {
    Shell shell;
    shell.Run();
  }

 private:
  int n_;
  int m_;
  Graph g_{0};
  long long min_cut_capacity_{0};
  std::vector<int> cut_edges_;

  void Run() {
    ReadInput();
    Execute();
    PrintResult();
  }
  void ReadInput() {
    std::cin >> n_ >> m_;
    g_ = Graph(n_);
    for (int i = 0; i < m_; ++i) {
      int u;
      int v;
      int c;
      std::cin >> u >> v >> c;
      g_.AddEdge(u, v, c, i + 1);
    }
  }

  void Execute() {
    int source = 1;
    int sink = n_;
    min_cut_capacity_ = g_.MaxFlow(source, sink);
    g_.FindReachableFromSource(source);
    cut_edges_ = g_.GetMinCutEdges();
  }

  void PrintResult() {
    std::cout << cut_edges_.size() << " " << min_cut_capacity_ << "\n";
    for (size_t i = 0; i < cut_edges_.size(); ++i) {
      if (i > 0) {
        std::cout << " ";
      }
      std::cout << cut_edges_[i];
    }
    std::cout << "\n";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Shell::Start();
}