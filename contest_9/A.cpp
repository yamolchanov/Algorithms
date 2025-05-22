#include <iostream>
#include <vector>

struct Graph {
  int n;
  int k;
  std::vector<std::vector<int>> adj;
  Graph(int n, int k) : n(n), k(k), adj(n) {}
  void AddEdge(int u, int v) { adj[u].push_back(v); }
};

class Shell {
public:
  void Run() {
    ReadInput();
    Kuhn();
    Result();
  }

private:
  int n_;
  int k_;
  Graph g_{0, 0};
  std::vector<int> mt_;
  std::vector<bool> used_;

  void ReadInput() {
    std::cin >> n_ >> k_;
    g_ = Graph(n_, k_);
    mt_.assign(k_, -1);
    used_.assign(n_, false);

    for (int i = 0; i < n_; ++i) {
      int j;
      std::cin >> j;
      while (j != 0) {
        g_.AddEdge(i, j - 1);
        std::cin >> j;
      }
    }
  }

  void Kuhn() {
    for (int v = 0; v < n_; ++v) {
      used_.assign(n_, false);
      TryKuhn(v);
    }
  }

  bool TryKuhn(int v) {
    if (used_[v]) {
      return false;
    }
    used_[v] = true;
    for (int to : g_.adj[v]) {
      if (mt_[to] == -1 || TryKuhn(mt_[to])) {
        mt_[to] = v;
        return true;
      }
    }
    return false;
  }

  void Result() {
    int count = 0;
    for (int i = 0; i < k_; ++i) {
      if (mt_[i] != -1) {
        ++count;
      }
    }
    std::cout << count << "\n";
    for (int i = 0; i < k_; ++i) {
      if (mt_[i] != -1) {
        std::cout << mt_[i] + 1 << " " << i + 1 << "\n";
      }
    }
  }
};

int main() {
  Shell shell;
  shell.Run();
}