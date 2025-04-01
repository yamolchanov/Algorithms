#include <algorithm>
#include <iostream>
#include <vector>

struct Graph {
 private:
  int n_;
  int timer_;
  std::vector<std::vector<std::pair<int, int>>> adj_;
  std::vector<int> tin_;
  std::vector<int> fup_;
  std::vector<std::string> color_;
  std::vector<int> bridges_;

 public:
  explicit Graph(int nodes, int m) : n_(nodes), timer_(0) {
    adj_.resize(n_ + 1);
    tin_.resize(n_ + 1, -1);
    fup_.resize(n_ + 1, -1);
    color_.resize(n_ + 1, "WHITE");
    for (int i = 1; i <= m; ++i) {
      int u;
      int v;
      std::cin >> u >> v;
      AddEdge(u, v, i);
    }
    FindBridge();
    std::cout << bridges_.size() << "\n";
    std::sort(bridges_.begin(), bridges_.end());
    for (int bridge : bridges_) {
      std::cout << bridge << " ";
    }
    std::cout << "\n";
  }

 private:
  void AddEdge(int u, int v, int id) {
    if (u != v) {
      adj_[u].push_back({v, id});
      adj_[v].push_back({u, id});
    }
  }
  void DFS(int v, int p_edge_id = -1) {
    color_[v] = "GREY";
    tin_[v] = timer_;
    fup_[v] = timer_;
    timer_++;
    for (auto [to, edge_id] : adj_[v]) {
      if (edge_id == p_edge_id) {
        continue;
      }
      if (color_[to] == "GREY") {
        fup_[v] = std::min(fup_[v], tin_[to]);
      } else if (color_[to] == "WHITE") {
        DFS(to, edge_id);
        fup_[v] = std::min(fup_[v], fup_[to]);
        if (fup_[to] > tin_[v]) {
          bridges_.push_back(edge_id);
        }
      }
    }
    color_[v] = "BLACK";
  }
  void FindBridge() {
    for (int i = 1; i <= n_; ++i) {
      if (color_[i] == "WHITE") {
        DFS(i);
      }
    }
  }
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  Graph graph(n, m);
}

