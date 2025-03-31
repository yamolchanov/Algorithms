#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Graph {
  int n;
  std::vector<std::vector<int>> e;
  std::vector<std::vector<int>> er;
  std::vector<std::string> was;
  std::vector<int> order;
  std::vector<int> comp;
  std::vector<int> ans;
  int cnt;
  explicit Graph(int n)
      : n(n), e(n), er(n), was(n, "white"), ans(n, 0), cnt(0) {}

  void ADD(int a, int b) {
    e[a].push_back(b);
    er[b].push_back(a);
  }

  void DFS1(int v) {
    was[v] = "grey";
    for (int u : e[v]) {
      if (was[u] == "white") {
        DFS1(u);
      }
    }
    was[v] = "black";
    order.push_back(v);
  }

  void DFS2(int v) {
    was[v] = "grey";
    comp.push_back(v);
    ans[v] = cnt;
    for (int u : er[v]) {
      if (was[u] == "white") {
        DFS2(u);
      }
    }
    was[v] = "black";
  }

  void Solve() {
    for (int i = 0; i < n; ++i) {
      if (was[i] == "white") {
        DFS1(i);
      }
    }
    std::ranges::fill(was, "white");
    std::ranges::reverse(order);
    for (const int cV : order) {
      if (was[cV] == "white") {
        DFS2(cV);
        ++cnt;
        comp.clear();
      }
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;

  Graph g(n);

  for (int i = 0; i < m; ++i) {
    int a;
    int b;
    std::cin >> a >> b;
    a--;
    b--;
    g.ADD(a, b);
  }
  g.Solve();
  std::cout << g.cnt << "\n";
  for (int i = 0; i < n; ++i) {
    std::cout << g.ans[i] + 1 << " ";
  }
  std::cout << "\n";
}

