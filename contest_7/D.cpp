#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Graph {
 private:
  int n_;
  int cnt_;
  std::vector<std::vector<int>> e_;
  std::vector<std::vector<int>> er_;
  std::vector<std::string> was_;
  std::vector<int> order_;
  std::vector<int> comp_;
  std::vector<int> ans_;
  void ADD(int a, int b) {
    e_[a].push_back(b);
    er_[b].push_back(a);
  }
  void EnterGraph(int m) {
    for (int i = 0; i < m; ++i) {
      int a;
      int b;
      std::cin >> a >> b;
      a--;
      b--;
      ADD(a, b);
    }
    Solve();
  }

  void DFS1(int v) {
    was_[v] = "grey";
    for (int u : e_[v]) {
      if (was_[u] == "white") {
        DFS1(u);
      }
    }
    was_[v] = "black";
    order_.push_back(v);
  }

  void DFS2(int v) {
    was_[v] = "grey";
    comp_.push_back(v);
    ans_[v] = cnt_;
    for (int u : er_[v]) {
      if (was_[u] == "white") {
        DFS2(u);
      }
    }
    was_[v] = "black";
  }

  void Solve() {
    
    for (int i = 0; i < n_; ++i) {
      if (was_[i] == "white") {
        DFS1(i);
      }
    }
    
    std::ranges::fill(was_, "white");
    std::ranges::reverse(order_);
    for (const int cV : order_) {
      if (was_[cV] == "white") {
        DFS2(cV);
        ++cnt_;
        comp_.clear();
      }
    }
    
    std::cout << cnt_ << "\n";
    
    for (int i = 0; i < n_; ++i) {
      std::cout << ans_[i] + 1 << " ";
    }
    
    std::cout << "\n";
  }

 public:
  explicit Graph(int n, int m)
      : n_(n), cnt_(0), e_(n), er_(n), was_(n, "white"), ans_(n, 0) {
    EnterGraph(m);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
}

