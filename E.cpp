#include <algorithm>
#include <iostream>
#include <vector>

struct Graph {
  int n;
  int timer;
  std::vector<std::vector<std::pair<int, int>>> adj;
  std::vector<int> tin, fup;
  std::vector<std::string> color;
  std::vector<int> bridges;
  explicit Graph(int nodes) : n(nodes), timer(0) {
    adj.resize(n + 1);
    tin.resize(n + 1, -1);
    fup.resize(n + 1, -1);
    color.resize(n + 1, "WHITE");
  }
  void AddEdge(int u, int v, int id) {
    if (u != v) {
      adj[u].push_back({v, id});
      adj[v].push_back({u, id});
    }
  }
  void DFS(int v, int p_edge_id = -1) {
    color[v] = "GREY";
    tin[v] = timer;
    fup[v] = timer;
    timer++;
    for (auto [to, edge_id] : adj[v]) {
      if (edge_id == p_edge_id) {
        continue;
      }
      if (color[to] == "GREY") {
        fup[v] = std::min(fup[v], tin[to]);
      } else if (color[to] == "WHITE") {
        DFS(to, edge_id);
        fup[v] = std::min(fup[v], fup[to]);
        if (fup[to] > tin[v]) {
          bridges.push_back(edge_id);
        }
      }
    }
    color[v] = "BLACK";
  }
  void FindBridge() {
    for (int i = 1; i <= n; ++i) {
      if (color[i] == "WHITE") {
        DFS(i);
      }
    }
  }
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 1; i <= m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    graph.AddEdge(u, v, i);
  }
  graph.FindBridge();
  std::cout << graph.bridges.size() << "\n";
  std::sort(graph.bridges.begin(), graph.bridges.end());
  for (int bridge : graph.bridges) {
    std::cout << bridge << " ";
  }
  std::cout << "\n";
}

