#include <iostream>
#include <vector>

struct Graph {
  int n;
  int k;
  std::vector<std::vector<int>> adj;
  Graph(int n, int k) : n(n), k(k), adj(n) {}
  void AddEdge(int u, int v) { adj[u].push_back(v); }
};

bool TryKuhn(int v, const Graph& g, std::vector<bool>& used,
             std::vector<int>& mt) {
  if (used[v]) {
    return false;
  }
  used[v] = true;
  for (int to : g.adj[v]) {
    if (mt[to] == -1 || TryKuhn(mt[to], g, used, mt)) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

void Solve() {
  int n;
  int k;
  std::cin >> n >> k;
  int count = 0;
  Graph g(n, k);
  std::vector<int> mt(k, -1);
  std::vector<bool> used(n);
  for (int i = 0; i < n; ++i) {
    int j;
    std::cin >> j;
    while (j != 0) {
      g.AddEdge(i, j - 1);
      std::cin >> j;
    }
  }
  for (int v = 0; v < n; ++v) {
    used.assign(n, false);
    TryKuhn(v, g, used, mt);
  }
  for (int i = 0; i < k; ++i) {
    if (mt[i] != -1) {
      ++count;
    }
  }
  std::cout << count << "\n";
  for (int i = 0; i < k; ++i) {
    if (mt[i] != -1) {
      std::cout << mt[i] + 1 << " " << i + 1 << "\n";
    }
  }
}

int main() { Solve(); }
