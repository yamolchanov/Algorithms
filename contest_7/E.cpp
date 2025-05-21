#include <algorithm>
#include <iostream>
#include <vector>

struct GraphShell {
  std::vector<int> tin;
  std::vector<int> fup;
  std::vector<std::string> color;
  std::vector<int> bridges;

  explicit GraphShell(int n) {
    tin.resize(n + 1, -1);
    fup.resize(n + 1, -1);
    color.resize(n + 1, "WHITE");
  }
};

struct Graph {
private:
  int n_;
  int timer_;
  std::vector<std::vector<std::pair<int, int>>> adj_;
  GraphShell shell_;

public:
  explicit Graph(int nodes) : n_(nodes), timer_(0), shell_(nodes) {
    adj_.resize(n_ + 1);
  }

  void AddEdge(int u, int v, int id) {
    if (u != v) {
      adj_[u].push_back({v, id});
      adj_[v].push_back({u, id});
    }
  }

  void Solve() {
    FindBridge();
    std::cout << shell_.bridges.size() << "\n";
    std::sort(shell_.bridges.begin(), shell_.bridges.end());
    for (int bridge : shell_.bridges) {
      std::cout << bridge << " ";
    }
    std::cout << "\n";
  }

private:
  void DFS(int v, int p_edge_id = -1) {
    shell_.color[v] = "GREY";
    shell_.tin[v] = timer_;
    shell_.fup[v] = timer_;
    timer_++;
    for (auto [to, edge_id] : adj_[v]) {
      if (edge_id == p_edge_id) continue;
      if (shell_.color[to] == "GREY") {
        shell_.fup[v] = std::min(shell_.fup[v], shell_.tin[to]);
      } else if (shell_.color[to] == "WHITE") {
        DFS(to, edge_id);
        shell_.fup[v] = std::min(shell_.fup[v], shell_.fup[to]);
        if (shell_.fup[to] > shell_.tin[v]) {
          shell_.bridges.push_back(edge_id);
        }
      }
    }
    shell_.color[v] = "BLACK";
  }

  void FindBridge() {
    for (int i = 1; i <= n_; ++i) {
      if (shell_.color[i] == "WHITE") {
        DFS(i);
      }
    }
  }
};

void Solve() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    std::cin >> u >> v;
    graph.AddEdge(u, v, i);
  }
  graph.Solve();
}

int main() {
  Solve();
}