#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Shell {
 public:
  std::vector<std::string> was;
  std::vector<int> order;
  std::vector<int> comp;
  std::vector<int> ans;

  Shell(int n) : was(n, "white"), ans(n, 0) {}

  void ResetWas() { std::ranges::fill(was, "white"); }

  void ClearComp() { comp.clear(); }
};

class Graph {
 public:
  int n;
  std::vector<std::vector<int>> e;
  std::vector<std::vector<int>> er;

  Graph(int n, int m) : n(n), e(n), er(n) {
    for (int i = 0; i < m; ++i) {
      int a;
      int b;
      std::cin >> a >> b;
      a--;
      b--;
      AddEdge(a, b);
    }
  }

  void AddEdge(int a, int b) {
    e[a].push_back(b);
    er[b].push_back(a);
  }
};

void DFS1(int v, const Graph& g, Shell& shell) {
  shell.was[v] = "grey";
  for (int u : g.e[v]) {
    if (shell.was[u] == "white") {
      DFS1(u, g, shell);
    }
  }
  shell.was[v] = "black";
  shell.order.push_back(v);
}

void DFS2(int v, const Graph& g, Shell& shell, int cnt) {
  shell.was[v] = "grey";
  shell.comp.push_back(v);
  shell.ans[v] = cnt;
  for (int u : g.er[v]) {
    if (shell.was[u] == "white") {
      DFS2(u, g, shell, cnt);
    }
  }
  shell.was[v] = "black";
}

void Solve(const Graph& g, Shell& shell) {
  int cnt = 0;

  for (int i = 0; i < g.n; ++i) {
    if (shell.was[i] == "white") {
      DFS1(i, g, shell);
    }
  }

  shell.ResetWas();
  std::ranges::reverse(shell.order);

  for (int v : shell.order) {
    if (shell.was[v] == "white") {
      DFS2(v, g, shell, cnt);
      ++cnt;
      shell.ClearComp();
    }
  }

  std::cout << cnt << "\n";
  for (int x : shell.ans) {
    std::cout << x + 1 << " ";
  }
  std::cout << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  int m;
  std::cin >> n >> m;

  Graph g(n, m);
  Shell shell(n);
  Solve(g, shell);
}