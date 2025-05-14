#include <iostream>
#include <vector>

bool TryKuhn(int v, std::vector<std::vector<int>>& g, std::vector<bool>& used,
             std::vector<int>& mt) {
  if (used[v]) {
    return false;
  }
  used[v] = true;
  for (size_t i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (mt[to] == -1 || TryKuhn(mt[to], g, used, mt)) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

int main() {
  int n;
  int k;
  std::vector<std::vector<int>> graph;
  std::vector<int> mt;
  std::vector<bool> used;
  std::cin >> n >> k;
  mt.assign(k, -1);
  graph.resize(n);

  for (int i = 0; i < n; i++) {
    int j;
    std::cin >> j;
    while (j != 0) {
      j--;
      graph[i].push_back(j);
      std::cin >> j;
    }
  }

  for (int v = 0; v < n; ++v) {
    used.assign(n, false);
    TryKuhn(v, graph, used, mt);
  }
  int count = 0;

  for (int i = 0; i < k; ++i) {
    if (mt[i] != -1) {
      count++;
    }
  }
  std::cout << count << "\n";
  for (int i = 0; i < k; ++i) {
    if (mt[i] != -1) {
      std::cout << mt[i] + 1 << " " << i + 1 << "\n";
    }
  }
}
